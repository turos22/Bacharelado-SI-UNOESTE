import Foundation
import SwiftUI
import UIKit

class PDFManager: ObservableObject {
    
    @Published var grupoSelecionado: String = "Anexos"
    @Published var logins: [Evento] = []
    @Published var evento: Evento?
    
    var materiaisFiltrados: [Material] {
        evento?.turmas.first?.materiais.filter { $0.grupo == grupoSelecionado } ?? []
    }

    func fetchEvento() {
        guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else {
            print("URL inválida")
            return
        }

        URLSession.shared.dataTask(with: url) { [weak self] data, _, error in
            guard let data = data, error == nil else {
                print("Erro na requisição: \(error?.localizedDescription ?? "Erro desconhecido")")
                return
            }

            do {
                let eventos = try JSONDecoder().decode([Evento].self, from: data)
                DispatchQueue.main.async {
                    self?.evento = eventos.first
                    print("Evento carregado com sucesso")
                }
            } catch {
                print("Erro ao decodificar JSON: \(error)")
            }
        }.resume()
    }


    func downloadPDF(from link: String, nome: String) {
        guard let url = URL(string: link) else { return }

        URLSession.shared.downloadTask(with: url) { tempURL, response, error in
            guard let tempURL = tempURL else {
                print("Erro ao baixar: \(error?.localizedDescription ?? "Erro desconhecido")")
                return
            }

            let fileManager = FileManager.default
            let documentsURL = fileManager.urls(for: .documentDirectory, in: .userDomainMask)[0]
            let destinationURL = documentsURL.appendingPathComponent("\(nome).pdf")

            do {
                if fileManager.fileExists(atPath: destinationURL.path) {
                    try fileManager.removeItem(at: destinationURL)
                }

                try fileManager.moveItem(at: tempURL, to: destinationURL)

                DispatchQueue.main.async {
                    self.sharePDF(at: destinationURL)
                }
            } catch {
                print("Erro ao mover arquivo: \(error)")
            }
        }.resume()
    }

    
    // MARK: - PUT para salvar no backend
    func putEvento() {
    guard let evento = self.evento else { return }

    guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else { return }

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
    
    private func sharePDF(at url: URL) {
        let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)

        if let windowScene = UIApplication.shared.connectedScenes.first as? UIWindowScene,
           let rootVC = windowScene.windows.first?.rootViewController {
            rootVC.present(activityVC, animated: true)
        }
    }

    // MARK: - Adicionar material
    func adicionarMaterial() {
        guard var evento = evento else { return }
        guard evento.turmas.indices.contains(0) else { return }

        let novoMaterial = Material(
            id: Int.random(in: 100...999),
            nome: "Novo PDF \(Int.random(in: 100...999))",
            link: "http://exemplo.com/novo.pdf",
            grupo: grupoSelecionado
        )

        var turma = evento.turmas[0]
        turma.materiais.append(novoMaterial)
        evento.turmas[0] = turma
        self.evento = evento

        putEvento()
    }

    // MARK: - Deletar material
    func deletarMaterial(_ material: Material) {
        guard var evento = evento else { return }
        guard evento.turmas.indices.contains(0) else { return }

        var turma = evento.turmas[0]
        turma.materiais.removeAll { $0.id == material.id }
        evento.turmas[0] = turma
        self.evento = evento

        putEvento()
    }
    
    func adicionarMaterialComArquivo(url: URL) {
        guard var evento = self.evento else { return }
        guard evento.turmas.indices.contains(0) else { return }

        let nome = url.lastPathComponent
        let link = url.absoluteString

        let novoMaterial = Material(
            id: Int.random(in: 1000...9999),
            nome: nome,
            arquivo: nome,
            link: link,
            status: 1,
            grupo: grupoSelecionado
        )

        // ✅ Adiciona diretamente nos materiais da turma 0
        self.evento?.turmas[0].materiais.append(novoMaterial)

        // ✅ Envia o evento completo atualizado
        putEvento()
    }


}
