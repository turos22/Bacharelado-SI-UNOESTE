import SwiftUI

func formatarData(_ isoString: String) -> String {
    let formatter = ISO8601DateFormatter()
    if let date = formatter.date(from: isoString) {
        let displayFormatter = DateFormatter()
        displayFormatter.dateStyle = .medium
        displayFormatter.timeStyle = .short
        return displayFormatter.string(from: date)
    }
    return isoString
}

struct TirarFotoView: View {
    
    // Parametros da tela
    @State var tipoUsuario: Int = 1 // 1 admin / 2 usuario
    @State var idusuario: Int = 2;
    
    // Pagina de confirmaçao
    @State private var confirmarFoto = false
    
    // viewModel
    @StateObject var viewModel = ViewModelPresenca()
    
    @State private var flagPresenca: Bool = false
    
    
    var body: some View {
        NavigationStack {
            ZStack {
                LinearGradient(
                    gradient: Gradient(colors: [Color("VermelhoHacka"), Color("AzulHacka")]),
                    startPoint: .top,
                    endPoint: .bottom
                )
                .edgesIgnoringSafeArea(.top)
                
                if viewModel.isLoading {
                    ProgressView("Carregando...")
                        .progressViewStyle(CircularProgressViewStyle(tint: .white))
                        .font(.title).foregroundColor(.white)
                    
                } else {
                    
                    // aqui vai fazer a logica
                    
                    // se é admin
                    if tipoUsuario == 1 {
                        VStack(alignment: .leading, spacing: 16) {
                            Text("Lista de Presenças")
                                .font(.system(size: 28, weight: .bold))
                                .foregroundColor(.white)
                                .padding()
                            
                            if let evento = viewModel.eventos.first,
                               let turma = evento.turmas.first {
                                
                                if turma.presencas.isEmpty {
                                    Text("Nenhuma presença registrada ainda.")
                                        .foregroundColor(.white)
                                        .padding()
                                } else {
                                    ScrollView {
                                        ForEach(turma.presencas, id: \.id) { presenca in
                                            HStack(alignment: .top, spacing: 12) {
                                                AsyncImage(url: URL(string: presenca.foto)) { image in
                                                    image
                                                        .resizable()
                                                        .aspectRatio(contentMode: .fill)
                                                } placeholder: {
                                                    ProgressView()
                                                }
                                                .frame(width: 60, height: 60)
                                                .clipShape(Circle())
                                                
                                                VStack(alignment: .leading) {
                                                    // Nome do aluno
                                                    if let usuario = turma.usuarios.first(where: { $0.id == presenca.aluno_id }) {
                                                        Text(usuario.nome ?? "Aluno sem nome")
                                                            .font(.headline)
                                                            .foregroundColor(.white)
                                                    } else {
                                                        Text("Aluno ID: \(presenca.aluno_id)")
                                                            .foregroundColor(.white)
                                                    }
                                                    
                                                    // Data formatada
                                                    Text(formatarData(presenca.data))
                                                        .font(.subheadline)
                                                        .foregroundColor(.gray)
                                                }
                                                
                                                Spacer()
                                            }
                                            .padding(.horizontal)
                                            .padding(.vertical, 8)
                                            .background(Color.white.opacity(0.1))
                                            .cornerRadius(10)
                                            .padding(.horizontal)
                                        }
                                    }
                                }
                            } else {
                                Text("Evento ou turma não encontrados.")
                                    .foregroundColor(.white)
                                    .padding()
                            }
                            
                            Spacer()
                        }
                    }
                    else
                    {
                        
                        if flagPresenca { // se ja fez o checkin
                            //                            Text("Presença marcada ✅")
                            
                            VStack{
                                
                                Spacer()
                                
                                if let evento = viewModel.eventos.first {
                                    if let turma = evento.turmas.first {
                                        ForEach(turma.usuarios, id: \.id) { usuario in
                                            if usuario.id == idusuario {
                                                Text("Olá, \(usuario.nome ?? "Aluno")")
                                                    .font(.system(size: 32, weight: .bold))
                                                    .foregroundColor(.white)
                                                    .padding(.horizontal)
                                                    .padding(.top, 5)
                                                    .frame(maxWidth: .infinity)
                                            }
                                        }
                                    }
                                }
                                
                                
                                Text("Presença Enviada!")
                                    .font(.system(size: 32, weight: .bold))
                                    .foregroundColor(.white)
                                    .padding(.horizontal)
                                    .padding(.top, 5)
                                    .frame(maxWidth: .infinity)
                                
                                Text("Você ja efetivou sua presença hoje.")
                                    .font(.system(size: 18))
                                    .foregroundColor(.white)
                                    .padding(2)
                                
                                
                                AsyncImage(url: URL(string: "https://images.emojiterra.com/microsoft/fluent-emoji/15.1/512px/2705_color.png")) { image in
                                    image
                                        .resizable()
                                        .aspectRatio(contentMode: .fill)
                                } placeholder: {
                                    ProgressView()
                                }
                                .frame(width: 270, height: 270)
                                .clipShape(RoundedRectangle(cornerRadius: 10))
                                .padding()
                                
                                Spacer()
                                
                            }
                            
                            
                        } else {// se nao fez o checkin
                            //                            Text("Presença não marcada ❌")
                            VStack {
                                Text("Marcar Presença")
                                    .font(.system(size: 32, weight: .bold))
                                    .foregroundColor(.white)
                                    .padding(.horizontal)
                                    .padding(.top, 5)
                                    .frame(maxWidth: .infinity)
                                
                                //                                Text("A foto enviada passará por um processo de aprovação, por isso é necessário seguir as regras de envio para não ficar com falta:")
                                //                                    .font(.system(size: 18))
                                //                                    .foregroundColor(.white)
                                //                                    .padding(2)
                                
                                if let evento = viewModel.eventos.first {
                                    if let turma = evento.turmas.first {
                                        ForEach(turma.usuarios, id: \.id) { usuario in
                                            if usuario.id == idusuario {
                                                Text("Olá, \(usuario.nome ?? "Aluno")")
                                                    .font(.system(size: 32, weight: .bold))
                                                    .foregroundColor(.white)
                                                    .padding(.horizontal)
                                                    .padding(.top, 5)
                                                    .frame(maxWidth: .infinity)
                                            }
                                        }
                                    }
                                }
                                
                                Text("- Seu rosto deve estar visível e próximo")
                                    .font(.system(size: 18))
                                    .foregroundColor(.white)
                                    .padding(.top,5)
                                Text("- Não faça gestos com as mãos")
                                    .font(.system(size: 18))
                                    .foregroundColor(.white)
                                    .padding(.top,5)
                                
                             
                                
//                                                            Text(viewModel.eventos.first?.nome ?? "Sem nome")
                                                                .font(.system(size: 18))
                                //                                .foregroundColor(.white)
                                //                                .padding(.top,5)
                                
                                
                                Spacer()
                                
                                AsyncImage(url: URL(string: "https://image-cdn-ak.spotifycdn.com/image/ab67706c0000da8463bcdace67f79859e30a17fa")) { image in
                                    image
                                        .resizable()
                                        .aspectRatio(contentMode: .fill)
                                } placeholder: {
                                    ProgressView()
                                }
                                .frame(width: 270, height: 270)
                                .clipShape(RoundedRectangle(cornerRadius: 10))
                                .padding()
                                
                                Spacer()
                                
                                Button(action: {
                                    print("Botão da câmera pressionado")
                                    confirmarFoto = true
                                }) {
                                    ZStack {
                                        Circle()
                                            .fill(Color.gray.opacity(0.8))
                                            .frame(width: 80, height: 80)
                                        
                                        Circle()
                                            .stroke(Color.white, lineWidth: 4)
                                            .frame(width: 70, height: 70)
                                    }
                                }
                                .buttonStyle(PlainButtonStyle())
                                .shadow(radius: 5)
                                
                                Spacer()
                            }
                            
                        }
                    }
                }
            }
            .navigationDestination(isPresented: $confirmarFoto) {
                if let evento = viewModel.eventos.first {
                    ConfirmarFotoView(viewModel: viewModel, eventoOriginal: evento, idusuario: idusuario, onDismiss: {
                        viewModel.fetch(numero: 0) // 🔁 Recarrega ao voltar
                    })
                } else {
                    Text("Erro ao carregar evento")
                }
            }
            
        }
        .edgesIgnoringSafeArea(.top)
        .onAppear {
            viewModel.fetch(numero: 0)
        }
        .onChange(of: viewModel.eventos) { _, novosEventos in
            flagPresenca = novosEventos.first?.turmas.first?.presencas.contains(where: { $0.aluno_id == idusuario }) ?? false
        }
    }
}

#Preview {
    TirarFotoView()
}
