import SwiftUI

struct ConfirmarFotoView: View {
    @ObservedObject var viewModel: ViewModelPresenca
    var eventoOriginal: Evento
    var idusuario: Int

    @Environment(\.dismiss) var dismiss
    @State private var eventoParaEnviar: Evento
    
    @State private var isLoading = false
    @State private var redirecionar = false
    
    var onDismiss: (() -> Void)? = nil
    
    // destination
    
    @State var destinationFlag: Bool = false

    // Inicializador personalizado para inicializar o evento editável
    init(viewModel: ViewModelPresenca, eventoOriginal: Evento, idusuario: Int, onDismiss: (() -> Void)? = nil) {
        self.onDismiss = onDismiss
        self.viewModel = viewModel
        self.eventoOriginal = eventoOriginal
        self.idusuario = idusuario
        _eventoParaEnviar = State(initialValue: eventoOriginal) // cria cópia local para editar
    }

    var body: some View {
        ZStack {
            LinearGradient(
                gradient: Gradient(colors: [Color("VermelhoHacka"), Color("AzulHacka")]),
                startPoint: .top,
                endPoint: .bottom
            )
            .edgesIgnoringSafeArea(.top)

            VStack {
                Text("Confirmar Foto")
                    .font(.system(size: 32, weight: .bold))
                    .foregroundColor(.white)
                    .padding(.horizontal)
                    .padding(.top, 5)
                    .frame(maxWidth: .infinity)

                Text("Enviar uma foto sem seguir as regras apresentadas poderá resultar em falta.")
                    .font(.system(size: 18))
                    .foregroundColor(.white)
                    .padding(2)
            

                Spacer()

                AsyncImage(url: URL(string: "https://img.freepik.com/psd-gratuitas/ilustracao-3d-de-avatar-ou-perfil-humano_23-2150671122.jpg")) { image in
                    image
                        .resizable()
                        .aspectRatio(contentMode: .fill)
                } placeholder: {
                    ProgressView()
                }
                .frame(width: 300, height: 300)
                .clipShape(RoundedRectangle(cornerRadius: 10))
                .padding()

                Spacer()

                Button(action: {
                    print("✅ Enviar pressionado")
                    isLoading = true // ativa loading

                    // sua lógica pra criar a nova presença
                    let novaPresenca = Presenca(
                        id: Int.random(in: 1000...9999),
                        aluno_id: idusuario,
                        data: ISO8601DateFormatter().string(from: Date()),
                        foto: "https://img.freepik.com/psd-gratuitas/ilustracao-3d-de-avatar-ou-perfil-humano_23-2150671122.jpg"
                    )
                    
                    eventoParaEnviar.turmas[0].presencas.append(novaPresenca)
                    
                    // chama o put e espera o retorno
                    viewModel.put(eventoParaEnviar) { success in
                        DispatchQueue.main.async {
                            
                            
                            destinationFlag = true
                            
                            // dando certo
//                            isLoading = false
//                            dismiss() // só fecha aqui, quando a requisição termina
//                            // se quiser fazer algo com redirecionar, use aqui
//                            redirecionar = true
//                            onDismiss?() // ✅ avisa a tela anterior para recarregar
                            
                            
                            
                        }
                    }

                })
                {
                    if isLoading {
                        ProgressView()
                            .progressViewStyle(CircularProgressViewStyle(tint: .white))
                            .frame(width: 100, height: 44)
                    } else {
                        Label("Enviar", systemImage: "checkmark")
                            .font(.title2)
                            .foregroundColor(.white)
                            .padding(.vertical, 14)
                            .padding(.horizontal, 40)
                            .background(Color.green)
                            .cornerRadius(12)
                    }
                }
                .disabled(isLoading)
                .navigationDestination(isPresented: $destinationFlag){
                    UsuarioView(usuarioId: idusuario)
                }

                Spacer()
            }
        }
    }
}

#Preview {
    let eventoExemplo = Evento(
        _id: nil,
        _rev: nil,
        id: nil,
        nome: nil,
        status: nil,
        calendario: [],
        turmas: []
    )

    return ConfirmarFotoView(
        viewModel: ViewModelPresenca(),
        eventoOriginal: eventoExemplo,
        idusuario: 1
    )
}
