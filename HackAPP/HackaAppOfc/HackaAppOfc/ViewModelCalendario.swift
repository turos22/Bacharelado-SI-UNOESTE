//
//  ViewModel.swift
//  TesteAi
//
//  Created by Turma02-2 on 18/07/25.
//

import Foundation

class ViewModelCalendario : ObservableObject{
    @Published var evento: [Evento] = []
  //  @Published var eventoTeste: [Evento] = []
    @Published var calendarios: [Calendario] = []
    @Published var turmas: [Turma] = []
    @Published var usuarios: [Usuario] = []
    @Published var postagens: [Postagem] = []
    @Published var materiais: [Material] = []
    @Published var presencas: [Presenca] = []
    
    func fetch(){
        guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else{
            return
        }
        
        let task = URLSession.shared.dataTask(with: url){ [weak self] data, _, error in
            
            guard let data = data, error == nil else{
                return
            }
            
            do{
//                let parsed = try JSONDecoder().decode([Persona].self, from: data)
                let parsedEvento = try JSONDecoder().decode([Evento].self, from: data)
                
                DispatchQueue.main.async {
                    self?.calendarios = parsedEvento.first?.calendario ?? []
                    self?.evento = parsedEvento
                    self?.turmas = parsedEvento.first?.turmas ?? []
                    
                    // Coleta todos os dados aninhados de turmas
                    self?.usuarios = parsedEvento.first?.turmas.flatMap { $0.usuarios } ?? []
                    self?.postagens = parsedEvento.first?.turmas.flatMap { $0.postagens } ?? []
                    self?.materiais = parsedEvento.first?.turmas.flatMap { $0.materiais } ?? []
                    self?.presencas = parsedEvento.first?.turmas.flatMap { $0.presencas } ?? []
                   // self?.eventoTeste = parsedEvento
                }
            }
            
            catch{
                print(error)
            }
            
        }
        
        task.resume()
    }
    func put(_ obj: Evento){ //Aqui deve ser colocado o nome da Struct relacionada
            
            guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else { return } //Aqui deve ser colocado o IP (local ou da rede) e, depois da barra, o verbo do POST do Node-RED
            
            var request = URLRequest(url: url)
            request.httpMethod = "PUT"
            
            var headers = request.allHTTPHeaderFields ?? [:]
            headers["Content-Type"] = "application/json"
            request.allHTTPHeaderFields = headers
            
            let encoder = JSONEncoder()
            
            do {
                let jsonData = try encoder.encode(obj)
                request.httpBody = jsonData
                print("jsonData: ", String(data: request.httpBody!, encoding: .utf8) ?? "no body data")
            } catch {
                print("Error encoding to JSON: \(error.localizedDescription)")
            }
            
            let task = URLSession.shared.dataTask(with: request) { data, response, error in
                if let error = error {
                    print("Error to send resource: \(error.localizedDescription)")
                    return
                }
                
                guard let httpResponse = response as? HTTPURLResponse else {
                    print("Error to send resource: invalid response")
                    return
                }
                
                if httpResponse.statusCode == 200 {
                    print("Resource POST successfully")
                } else {
                    print("Error POST resource: status code \(httpResponse.statusCode)")
                }
            }
            task.resume()
        }
}




