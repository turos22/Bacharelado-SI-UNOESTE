
import SwiftUI

struct ConfigView: View {
    var body: some View {
        NavigationStack{
            ZStack{
                Color.amareloHacka.ignoresSafeArea()
                ScrollView{
                    VStack{
                        Image("HackaLogoLight")
                            .resizable()
                            .scaledToFit()
                            .frame(width: 250)
                            .padding()
                        NavigationLink(destination: Usuarios()){
                            VStack{
                                ZStack{
                                    Rectangle()
                                        .frame(width: 200, height: 200)
                                        .cornerRadius(20)
                                        .foregroundColor(.azulClaro)
                                        .shadow(color: .black, radius: 3, x: 5, y: 5)
                                    Image(systemName: "person.fill")
                                        .resizable()
                                        .scaledToFit()
                                        .frame(width: 130)
                                        .foregroundColor(.white)
                                        .shadow(color: .gray, radius: 1, x: 5, y: 5)
                                    
                                }
                                Text("Novo Usuário")
                                    .bold()
                            }
                        }
                        .tint(.black)
                        NavigationLink(destination: Configuracao()){
                            VStack{
                                ZStack{
                                    Rectangle()
                                        .frame(width: 200, height: 200)
                                        .cornerRadius(20)
                                        .foregroundColor(.vermelhoHacka)
                                        .shadow(color: .black, radius: 3, x: 5, y: 5)
                                    Image(systemName: "newspaper.fill")
                                        .resizable()
                                        .scaledToFit()
                                        .frame(width: 130)
                                        .foregroundColor(.white)
                                        .shadow(color: .gray, radius: 1, x: 5, y: 5)
                                    
                                }
                                Text("Postagens")
                                    .bold()
                            }
                            
                        }
                        .tint(.black)
                        NavigationLink(destination: IAView()){
                            VStack{
                                ZStack{
                                    Rectangle()
                                        .fill(
                                                        RadialGradient(
                                                            gradient: Gradient(colors: [
                                                                .red, .orange, .yellow, .green, .blue, .purple
                                                            ]),
                                                            center: .center,
                                                            startRadius: 50,
                                                            endRadius: 120
                                                        )
                                                    )
                                        .frame(width: 200, height: 200)
                                        .cornerRadius(20)
                                    
                                        .shadow(color: .black, radius: 3, x: 5, y: 5)
                                    Image(systemName: "brain.fill")
                                        .resizable()
                                        .scaledToFit()
                                        .frame(width: 130)
                                        .foregroundColor(.white)
                                        .shadow(color: .gray, radius: 1, x: 5, y: 5)
                                    
                                }
                                Text("IA")
                                    .bold()
                            }
                            
                        }
                        .tint(.black)
                        NavigationLink(destination: telaLogin()){
                            VStack{
                                ZStack{
                                    Rectangle()
                                        .frame(width: 200, height: 200)
                                        .cornerRadius(20)
                                        .foregroundColor(.azulHacka)
                                        .shadow(color: .black, radius: 3, x: 5, y: 5)
                                    Image(systemName: "door.right.hand.open")
                                        .resizable()
                                        .scaledToFit()
                                        .frame(width: 110)
                                        .foregroundColor(.white)
                                        .shadow(color: .gray, radius: 1, x: 5, y: 5)
                                    
                                }
                                Text("Logout")
                                    .bold()
                            }
                            
                        }
                        .tint(.black)
                        
                        Spacer()
                    }
                }
            }
            
        }
    }
}

#Preview {
    ConfigView()
        .environmentObject(PostagemViewModel())
}
