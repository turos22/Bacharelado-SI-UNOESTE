//
//  ViewModel.swift
//  htppdog
//
//  Created by Turma02-16 on 14/07/25.
//

import Foundation

class ViewModelPresenca: ObservableObject {
    
    @Published var eventos: [Evento] = []
    @Published var isLoading: Bool = false  // <-- Adicionado controle de loading
    
    func fetch(numero: Int) {
        
        guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else {
            print("URL inválida")
            return
        }
        
        DispatchQueue.main.async {
            self.isLoading = true  // <-- Inicia loading antes da requisição
        }
        
        let task = URLSession.shared.dataTask(with: url) { [weak self] data, _, error in
            
            DispatchQueue.main.async {
                self?.isLoading = false  // <-- Termina loading após resposta
            }
            
            guard let data = data, error == nil else {
                print("Erro na requisição: \(error?.localizedDescription ?? "Desconhecido")")
                return
            }
            
            if let jsonString = String(data: data, encoding: .utf8) {
                print("📦 JSON recebido:\n\(jsonString)")
            } else {
                print("❌ Não foi possível converter os dados em String.")
            }
            
            do {
                let parsed = try JSONDecoder().decode([Evento].self, from: data)
                DispatchQueue.main.async {
                    self?.eventos = parsed
                }
            }
            catch {
                if let decodingError = error as? DecodingError {
                    switch decodingError {
                    case .typeMismatch(let type, let context):
                        print("🔴 Type mismatch for type \(type): \(context.debugDescription)")
                    case .valueNotFound(let type, let context):
                        print("🔴 Value not found for type \(type): \(context.debugDescription)")
                    case .keyNotFound(let key, let context):
                        print("🔴 Key '\(key.stringValue)' not found: \(context.debugDescription)")
                    case .dataCorrupted(let context):
                        print("🔴 Data corrupted: \(context.debugDescription)")
                    @unknown default:
                        print("❌ Erro desconhecido ao decodificar: \(decodingError)")
                    }
                } else {
                    print("❌ Erro geral: \(error)")
                }
            }
        }
        task.resume()
    }
    
    
    func put(_ obj: Evento, completion: @escaping (Bool) -> Void) { // Adicionei completion
        guard let url = URL(string: "http://192.168.128.10:1880/Usuario") else {
            completion(false)
            return
        }
        
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
            completion(false)
            return
        }
        
        let task = URLSession.shared.dataTask(with: request) { data, response, error in
            if let error = error {
                print("Error to send resource: \(error.localizedDescription)")
                completion(false)
                return
            }
            
            guard let httpResponse = response as? HTTPURLResponse else {
                print("Error to send resource: invalid response")
                completion(false)
                return
            }
            
            if httpResponse.statusCode == 200 {
                print("Resource PUT successfully")
                completion(true)
            } else {
                print("Error PUT resource: status code \(httpResponse.statusCode)")
                completion(false)
            }
        }
        task.resume()
    }

}
