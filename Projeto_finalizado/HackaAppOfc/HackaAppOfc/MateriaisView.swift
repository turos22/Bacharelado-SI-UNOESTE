import SwiftUI
import PDFKit

struct MateriaisView: View {
    @StateObject private var pdfManager = PDFManager()
    
    let grupos = ["Swift", "Arduino IDE", "Palestras"]
    @State private var mostrarPicker = false

    
    var body: some View {
        NavigationView {
            VStack {
                HStack {
                    Image("HackaLogoLight")
                        .resizable()
                        .scaledToFit()
                        .frame(height: 30)
                    Spacer()
                }
                .padding(.bottom, 5)
                
                ScrollView(.horizontal, showsIndicators: false) {
                    HStack(spacing: 16) {
                        ForEach(grupos, id: \.self) { grupo in
                            Button(action: {
                                pdfManager.grupoSelecionado = grupo
                            }) {
                                Text(grupo)
                                    .padding(.vertical, 8)
                                    .padding(.horizontal, 16)
                                    .background(pdfManager.grupoSelecionado == grupo ? Color.pink.opacity(0.9) : Color.gray.opacity(0.1))
                                    .foregroundColor(pdfManager.grupoSelecionado == grupo ? Color.white : Color.black)
                                    .cornerRadius(10)
                            }
                        }
                    }
                    .padding(.horizontal)
                }
                
                ScrollView {
                    VStack(alignment: .leading, spacing: 12) {
                        ForEach(pdfManager.materiaisFiltrados) { material in
                            HStack {
                                if let link = material.link, let url = URL(string: link) {
                                    NavigationLink(destination: PDFKitView(url: url)) {
                                        Text(material.nome ?? "Sem nome")
                                    }
                                }
                                
                                Spacer()
                                
                                if let link = material.link, let nome = material.nome {
                                    Button {
                                        pdfManager.downloadPDF(from: link, nome: nome)
                                    } label: {
                                        Image(systemName: "arrow.down.circle")
                                            .font(.title2)
                                    }
                                }
                            }
                            .padding()
                            .background(Color.gray.opacity(0.1))
                            .cornerRadius(10)
                        }
                    }
                    .padding(.top)
                }
                /*
                TabView {
                    VStack(spacing: 20) {
                        Image(systemName: "folder")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 10, height: 10)
                            .foregroundColor(.red)
                        Text("Arquivos")
                            .font(.callout)
                    }
                    .tabItem {
                        Label("Arquivos", systemImage: "folder")
                    }
                    
                    VStack(spacing: 20) {
                        Image(systemName: "checkmark.circle")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 80, height: 80)
                            .foregroundColor(.orange)
                        Text("Registro de presença")
                            .font(.title2)
                    }
                    .tabItem {
                        Label("Presença", systemImage: "checkmark.circle")
                    }
                    
                    VStack(spacing: 20) {
                        Image(systemName: "calendar")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 80, height: 80)
                            .foregroundColor(.green)
                        Text("Calendário do evento")
                            .font(.title2)
                    }
                    .tabItem {
                        Label("Calendário", systemImage: "calendar")
                    }
                    
                    VStack(spacing: 20) {
                        Image(systemName: "gear")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 80, height: 80)
                            .foregroundColor(.blue)
                        Text("Configurações do app")
                            .font(.title2)
                    }
                    .tabItem {
                        Label("Configurações", systemImage: "gear")
                    }
                }*/
            }
            .padding()
        }
        .onAppear {
            pdfManager.fetchEvento()
        }
    }
}


#Preview{
    MateriaisView()
}
