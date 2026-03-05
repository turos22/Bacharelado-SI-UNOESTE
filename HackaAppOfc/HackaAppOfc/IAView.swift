//
//  IAView.swift
//  TesteAi
//
//  Created by Turma02-2 on 17/07/25.
//

import SwiftUI
import GoogleGenerativeAI
import UniformTypeIdentifiers // Importado para UTType (necessário para o ActivityViewController)

struct IAView: View {
    let model = GenerativeModel(name: "gemini-2.0-flash", apiKey: APIKey.default)
    @State var texto = ""
    @State var resposta = "Salve Pai, o que tu quer?"
    @State private var perguntaPersonalizada: String = ""
    @StateObject var viewModel = ViewModelCalendario()

    @State private var showingShareSheet = false
    @State private var fileToShare: URL?
    @State private var cria_csv  = false

    var body: some View {
        ZStack {
            ZStack {
                LinearGradient(
                    gradient: Gradient(colors: [Color.azulHacka, Color.vermelhoHacka]),
                    startPoint: .center,
                    endPoint: .bottomTrailing
                )
                .ignoresSafeArea()

                ForEach(0..<80, id: \.self) { _ in
                    Circle()
                        .fill(Color.white.opacity(Double.random(in: 0.2...0.6)))
                        .frame(width: CGFloat.random(in: 1...3), height: CGFloat.random(in: 1...3))
                        .position(
                            x: CGFloat.random(in: 0...UIScreen.main.bounds.width),
                            y: CGFloat.random(in: 0...UIScreen.main.bounds.height)
                        )
                }
            }

            VStack { // VStack principal para organizar o conteúdo e o botão fixo
                ScrollView { // ScrollView para o conteúdo superior e a resposta
                    VStack { // Conteúdo que rola
                        AsyncImage(url: URL(string: "https://www.inovacao.usp.br/wp-content/uploads/sites/300/2019/08/2017_05_21-hackatruck1-520x245.png"),
                                   content: { image in
                            image.resizable()
                                .scaledToFill()
                                .frame(width: 350, height: 150)
                                .clipShape(RoundedRectangle(cornerRadius:10))
                        },
                                   placeholder: {
                            ProgressView()
                        }).padding()
                            
                        
                        HStack{
                            Text("Digite um texto abaixo:")
                                .foregroundStyle(Color.white)
                            Spacer()
                            Toggle(isOn: $cria_csv) {
                               Text("csv")
                                   .foregroundStyle(.white)
                            }.frame(width: 100, height: 50)

                           .onChange(of: cria_csv) {
                               valor in
                               if valor
                               {
                                   perguntaPersonalizada = "Colunas (x,y,z)"
                               }
                               else
                               {
                                   perguntaPersonalizada = ""
                               }
                           }
                            
                        }.padding(.leading)
                            .padding(.trailing)
                       

                        TextField("Teste", text: $perguntaPersonalizada)
                            .foregroundStyle(Color.white)
                            .background(.gray.opacity(0.2))
                            .cornerRadius(5)
                            .padding(.horizontal)
                            .font(.headline)
                            .padding(.bottom)

                        Button("Confirme") {
                            Task {
                                await consultarPresencas()
                            }
                        }
                        .padding()
                        .background(Color.azulClaro)
                        .foregroundStyle(.white)
                        .cornerRadius(10)

                        // A ScrollView anterior da resposta foi movida para fora deste VStack
                        Text(resposta)
                            .foregroundStyle(.white)
                            .padding()
                            .frame(maxWidth: .infinity, alignment: .leading) // Garante que a resposta ocupe a largura total
                    }
                    .padding()
                }

                Spacer()
                Button("Exportar Resposta para CSV") {
                    exportResponseToCSV(csvString: resposta)
                }
                .padding()
                .frame(maxWidth: .infinity) // Ocupa toda a largura horizontal
                .background(Color.green)
                .foregroundStyle(.white)
                .cornerRadius(10)
                .padding(.horizontal)
                .padding(.bottom)
                .disabled(!cria_csv)
                .opacity(cria_csv ? 1:0.3)
            }
        }
        .onAppear() {
            viewModel.fetch()
        }
        .sheet(isPresented: $showingShareSheet) {
            if let fileURL = fileToShare {
                ActivityViewController(activityItems: [fileURL])
            } else {
                Text("Erro ao preparar o arquivo para compartilhamento.")
            }
        }
    }

     func generateAIPrompt() -> String? {
        let encoder = JSONEncoder()
        encoder.outputFormatting = .prettyPrinted
        encoder.dateEncodingStrategy = .iso8601

        do {
            guard !viewModel.evento.isEmpty else {
                print("ViewModel.evento está vazio. Não é possível gerar prompt com dados.")
                return nil
            }

            let eventoData = try encoder.encode(viewModel.evento.first!)

            let calendarioData = try encoder.encode(viewModel.calendarios)
            let turmaData = try encoder.encode(viewModel.turmas)
            let usuarioData = try encoder.encode(viewModel.usuarios)
            let postagemData = try encoder.encode(viewModel.postagens)
            let materialData = try encoder.encode(viewModel.materiais)
            let presencasData = try encoder.encode(viewModel.presencas)
            
              guard let eventoString = String(data: eventoData, encoding: .utf8),
                    let calendarioString = String(data: calendarioData, encoding: .utf8),
                    let turmaString = String(data: turmaData, encoding: .utf8),
                    let usuarioString = String(data: usuarioData, encoding: .utf8),
                    let postagemString = String(data: postagemData, encoding: .utf8),
                    let materialString = String(data: materialData, encoding: .utf8),
                    let presencasString = String(data: presencasData, encoding: .utf8) else {
                  return nil
              }

            if cria_csv == true{
                let prompt = """
                --- INSTRUÇÕES PARA A RESPOSTA ---
                Sua única e exclusiva tarefa é gerar dados CSV.
                Se a pergunta do usuário for uma solicitação para gerar um arquivo CSV com colunas específicas, você DEVE retornar APENAS o conteúdo CSV.
                NÃO inclua qualquer texto introdutório, conclusivo, explicações, comentários, código Swift, JSON ou qualquer outro tipo de formatação além do CSV puro.
                O CSV deve começar imediatamente com a linha de cabeçalho e ser seguido pelas linhas de dados, separadas por vírgulas.
                NÃO use blocos de código (```) para envolver o CSV.
                Se a pergunta do usuário NÃO for sobre gerar um CSV, responda normalmente, mas mantenha a resposta concisa.
                Utilize APENAS os dados abaixo:
                                              **Evento:**
                                              ```json
                                              \(eventoString)
                                              ```

                                              **Calendários:**
                                              ```json
                                              \(calendarioString)
                                              ```

                                              **Turmas:**
                                              ```json
                                              \(turmaString)
                                              ```

                                              **Usuários:**
                                              ```json
                                              \(usuarioString)
                                              ```

                                              **Postagens:**
                                              ```json
                                              \(postagemString)
                                              ```

                                              **Materiais:**
                                              ```json
                                              \(materialString)
                                              ```

                                              **Presenças:**
                                              ```json
                                              \(presencasString)
                                              ```
                Faca um relatorio na melhor logica possivel, associando os dados de acordo com as colunas que o usuario digita, ou seja, caso ele escreva aluno, traga o nome do aluno do Usuarios, Presenca traga se o aluno estava presente ou nao
                Traga a data em um formato possivel para exportar para csv

                --- PERGUNTA DO USUÁRIO ---
                """
                
                return prompt

            }
            else
            {
                let prompt = """
                              Utilize os dados CASO EU COLOQUE NA PERGUNTA: (DADOS), CASO CONTRÁRIO PESQUISE NA INTERNET E FUNCIONE NORMALMENTE, porém não exiba-os, apenas mostre o resultado da pergunta utilizando-os:

                              **Evento:**
                              ```json
                              \(eventoString)
                              ```

                              **Calendários:**
                              ```json
                              \(calendarioString)
                              ```

                              **Turmas:**
                              ```json
                              \(turmaString)
                              ```

                              **Usuários:**
                              ```json
                              \(usuarioString)
                              ```

                              **Postagens:**
                              ```json
                              \(postagemString)
                              ```

                              **Materiais:**
                              ```json
                              \(materialString)
                              ```

                              **Presenças:**
                              ```json
                              \(presencasString)
                              ```

                              --- PERGUNTA ---
                              """
                return prompt

            }
              


        } catch {
            print("Erro ao codificar dados para JSON: \(error)")
            return nil
        }
    }
   
    // ONDE COMEÇA A FUNÇÃO DE EXPORTAÇÃO
    func exportResponseToCSV(csvString: String) {
        let filename = "export_dados.csv"
        let tempDir = FileManager.default.temporaryDirectory
        let fileURL = tempDir.appendingPathComponent(filename)

        do {
            try csvString.write(to: fileURL, atomically: true, encoding: .utf8)
            self.fileToShare = fileURL
            self.showingShareSheet = true
        } catch {
            print("Erro ao escrever string CSV para o arquivo: \(error.localizedDescription)")
            resposta = "Erro ao exportar CSV: \(error.localizedDescription)"
        }
    }
    // ONDE TERMINA A FUNÇÃO DE EXPORTAÇÃO

    func consultarPresencas() async {
        guard let basePrompt = generateAIPrompt() else {
            resposta = "Erro ao preparar os dados para a IA. Verifique se os dados estão carregados corretamente."
            return
        }

        let fullPrompt = "\(basePrompt)\n\(perguntaPersonalizada)"
        print("Enviando prompt completo para Gemini:\n\(fullPrompt)")

        resposta = "Consultando IA..."

        do {
            let response = try await model.generateContent(fullPrompt)
            
            if let text = response.text {
                resposta = text
                print("Resposta da IA:\n\(text)")
            } else {
                resposta = "Não foi possível obter uma resposta de texto da IA."
            }
        } catch {
            resposta = "Erro ao processar a resposta do modelo: \(error.localizedDescription)"
            print("Erro Gemini: \(error.localizedDescription)")
        }
    }

    func sendMessage() async {
        // Seu código para sendMessage, se aplicável.
    }

}

// UIActivityViewController Wrapper para SwiftUI (Você já tinha essa ou uma similar)
struct ActivityViewController: UIViewControllerRepresentable {
    var activityItems: [Any]
    var applicationActivities: [UIActivity]? = nil

    func makeUIViewController(context: UIViewControllerRepresentableContext<ActivityViewController>) -> UIActivityViewController {
        let controller = UIActivityViewController(activityItems: activityItems, applicationActivities: applicationActivities)
        return controller
    }

    func updateUIViewController(_ uiViewController: UIActivityViewController, context: UIViewControllerRepresentableContext<ActivityViewController>) {}
}


#Preview {
    IAView()
}
