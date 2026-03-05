import SwiftUI
import Foundation

struct Avisos: View {
    @StateObject var viewModel = PostagemViewModel()
    
    var fixado: Postagem? {
        viewModel.postagens.first { $0.fixado == 1 && $0.status == 1 }
    }
    
    var outrasPostagens: [Postagem] {
        viewModel.postagens.filter { $0.status == 1 && $0.fixado == 0 }
    }
    
    var body: some View {
        ZStack {
            // Fundo gradiente moderno
            LinearGradient(
                gradient: Gradient(colors: [Color.azulHacka, Color.vermelhoHacka.opacity(0.8)]),
                startPoint: .top,
                endPoint: .bottom
            )
            .edgesIgnoringSafeArea(.top)
            
            VStack(spacing: 20) {
                VStack {
                    Image("HackaLogoDark")
                        .resizable()
                        .scaledToFit()
                        .frame(height: 100)
                        .padding(.horizontal, 30)
                        .shadow(color: .black.opacity(0.1), radius: 3, x: 0, y: 2)
                }
                .padding(.top, 20)
                .padding(.bottom, 10)
                
                ScrollView {
                    VStack(spacing: 20) {
                        if let fixado = fixado {
                            PostagemView(postagem: fixado, isFixado: true)
                                .shadow(color: .black.opacity(0.1), radius: 5, x: 0, y: 2)
                        }
                        
                        ForEach(outrasPostagens) { postagem in
                            PostagemView(postagem: postagem, isFixado: false)
                                .transition(.opacity)
                        }
                        
                        if outrasPostagens.isEmpty {
                            VStack {
                                Image(systemName: "bell.slash.fill")
                                    .font(.system(size: 40))
                                    .foregroundColor(.gray.opacity(0.5))
                                    .padding(.bottom, 8)
                                
                                Text("Nenhum aviso no momento")
                                    .foregroundColor(.gray)
                            }
                            .padding(40)
                        }
                    }
                    .padding()
                    .padding(.bottom, 20)
                }
                .background(Color.white)
                .cornerRadius(30)
                .shadow(color: .black.opacity(0.1), radius: 20, x: 0, y: -5)
                .padding(.horizontal, 10)
            }
            .padding(.bottom)
            .onAppear(){
                viewModel.fetch()
            }
        }
    }
}

struct PostagemView: View {
    let postagem: Postagem
    let isFixado: Bool
    
    var body: some View {
        VStack(alignment: .leading, spacing: 12) {
            HStack(alignment: .top) {
                Image(systemName: isFixado ? "pin.fill" : "megaphone.fill")
                    .foregroundColor(isFixado ? .yellow : .blue)
                    .font(.system(size: 20))
                    .padding(.top, 2)
                
                VStack(alignment: .leading, spacing: 6) {
                    HStack {
                        Text(isFixado ? "FIXADO" : "AVISO")
                            .font(.system(size: 12, weight: .bold))
                            .foregroundColor(.white)
                            .padding(.horizontal, 8)
                            .padding(.vertical, 2)
                            .background(isFixado ? Color.orange : Color.blue)
                            .cornerRadius(10)
                        
                        Spacer()
                        
                        Text(formattedDate())
                            .font(.caption)
                            .foregroundColor(.gray)
                    }
                    
                    Text(postagem.titulo)
                        .font(.system(size: 18, weight: .semibold))
                        .foregroundColor(.primary)
                        .padding(.top, 2)
                    
                    
                    Text(postagem.conteudo)
                        .font(.system(size: 15))
                        .foregroundColor(.secondary)
                        .fixedSize(horizontal: false, vertical: true)
                }
            }
            
            if let imagemURL = postagem.imagem, !imagemURL.isEmpty {
                AsyncImage(url: URL(string: imagemURL)) { phase in
                    if let image = phase.image {
                        image
                            .resizable()
                            .scaledToFill()
                            .frame(maxWidth: .infinity)
                            .frame(height: 200)
                            .cornerRadius(12)
                            .clipped()
                    } else if phase.error != nil {
                        Image(systemName: "photo")
                            .frame(height: 80)
                            .foregroundColor(.gray)
                    } else {
                        ProgressView()
                            .frame(height: 80)
                    }
                }
                .padding(.vertical, 8)
            }
            
            HStack {
                if let link = postagem.link, !link.isEmpty {
                    Link(destination: URL(string: link)!) {
                        HStack(spacing: 4) {
                            Image(systemName: "link")
                            Text("Link")
                        }
                        .font(.system(size: 14, weight: .medium))
                        .foregroundColor(.blue)
                    }
                    .buttonStyle(.plain)
                }
                
                if let arquivo = postagem.arquivo, !arquivo.isEmpty {
                    HStack(spacing: 4) {
                        Image(systemName: "paperclip")
                        Text(arquivo)
                    }
                    .font(.system(size: 14))
                    .foregroundColor(.gray)
                }
                
                Spacer()
            }
        }
        .padding()
        .background(Color.white)
        .cornerRadius(16)
        .shadow(color: .black.opacity(0.05), radius: 8, x: 0, y: 2)
        .overlay(
            RoundedRectangle(cornerRadius: 16)
                .stroke(isFixado ? Color.yellow.opacity(0.5) : Color.gray.opacity(0.2), lineWidth: 1)
        )
    }
    
    private func formattedDate() -> String {
        let formatter = DateFormatter()
        formatter.dateStyle = .short
        formatter.timeStyle = .none
        return formatter.string(from: Date())
    }
}

#Preview {
    Avisos()
        .environmentObject(PostagemViewModel())
}
