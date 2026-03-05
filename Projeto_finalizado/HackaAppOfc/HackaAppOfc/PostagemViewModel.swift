import Foundation
import SwiftUI

class PostagemViewModel: ObservableObject {
    @Published var evento: Evento?
    @Published var postagens: [Postagem] = []
    @Published var calendario: [Calendario] = []
    @Published var turmas: [Turma] = []
    @Published var usuarios: [Usuario] = []
    @Published var materiais: [Material] = []
    @Published var presencas: [Presenca] = []
    
    @Published var isLoading: Bool = false
    @Published var errorMessage: String? = nil
    
    func fetch() {
        guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else {
            print("URL inválida")
            return
        }
        
        URLSession.shared.dataTask(with: url) { [weak self] data, _, error in
            guard let data = data, error == nil else {
                print("Erro na requisição:", error?.localizedDescription ?? "Erro desconhecido")
                return
            }
            
            do {
                let eventos = try JSONDecoder().decode([Evento].self, from: data)
                DispatchQueue.main.async {
                    self?.evento = eventos.first
                    self?.postagens = eventos.first?.turmas.first?.postagens ?? []
                }
            } catch {
                print("Erro ao decodificar JSON:", error)
            }
        }.resume()
    }
    
    private func atualizarPostagens() {
        guard let evento = self.evento else {return}
        
        guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else {return}
        
        var request = URLRequest(url: url)
        request.httpMethod = "PUT"
        request.addValue("application/json", forHTTPHeaderField: "Content-Type")
        
        let encoder = JSONEncoder()
        encoder.outputFormatting = .prettyPrinted
        
        do {
            let data = try encoder.encode(evento)
            request.httpBody = data
            
            print("Enviando JSON:\n", String(data: data, encoding: .utf8) ?? "")
            
            let task = URLSession.shared.dataTask(with: request) { data, response, error in
                if let error = error {
                    print("Erro ao enviar PUT: \(error.localizedDescription)")
                    return
                }
                
                if let response = response as? HTTPURLResponse {
                    print("PUT status: \(response.statusCode)")
                }
            }
            
            task.resume()
        } catch {
            print("Erro ao codificar evento: \(error)")
        }
    }
    
    func adicionarPostagem(postagem: Postagem) {
        guard var eventoLocal = evento else { return }
        
        let novoId = (postagens.map { $0.id }.max() ?? 0) + 1
        var novaPostagem = postagem
        novaPostagem.id = novoId
        
        postagens.append(novaPostagem)
        
        // Atualiza a turma dentro do evento localmente
        if !eventoLocal.turmas.isEmpty {
            eventoLocal.turmas[0].postagens = postagens
        }
        
        // Reatribui para atualizar @Published evento
        DispatchQueue.main.async {
            self.evento = eventoLocal
            self.atualizarPostagens()
        }
    }

    
    func editarPostagem(id: Int, novoTitulo: String, novoConteudo: String) {
        guard var eventoAtual = evento else { return }
        
        if let index = postagens.firstIndex(where: { $0.id == id }) {
            postagens[index].titulo = novoTitulo
            postagens[index].conteudo = novoConteudo
            
            if !eventoAtual.turmas.isEmpty {
                eventoAtual.turmas[0].postagens = postagens
                evento = eventoAtual
                atualizarPostagens()
            }
        }
    }
    
    func excluirLogicamente(id: Int) {
        guard var eventoAtual = evento else { return }
        
        if let index = postagens.firstIndex(where: { $0.id == id }) {
            postagens[index].status = 0
            // Opcional: Remover da lista visível local
            //postagens.remove(at: index)
            
            if !eventoAtual.turmas.isEmpty {
                eventoAtual.turmas[0].postagens = postagens
                evento = eventoAtual
                atualizarPostagens()
            }
        }
    }
    
    func fixarPostagem(id: Int) {
        guard var eventoAtual = evento else { return }
        
        // Verifica se a postagem já está fixada
        if let postagemAtual = postagens.first(where: { $0.id == id }), postagemAtual.fixado == 1 {
            // Já está fixada, então desfixa
            postagens = postagens.map {
                var p = $0
                p.fixado = 0
                return p
            }
        } else {
            // Não está fixada, então fixa esta e desfixa as demais
            postagens = postagens.map {
                var p = $0
                p.fixado = (p.id == id) ? 1 : 0
                return p
            }
        }

        // Atualiza na turma e sincroniza com o evento
        if !eventoAtual.turmas.isEmpty {
            eventoAtual.turmas[0].postagens = postagens
            evento = eventoAtual
            atualizarPostagens()
        }
    }

}
