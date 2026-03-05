//
//  telaLogin.swift
//  HackaApp
//
//  Created by Turma02-6 on 17/07/25.
//

import SwiftUI

enum AppTheme {
    case light, dark
}

class ThemeManager: ObservableObject {
    @Published var currentTheme: AppTheme = .light
}

struct telaLogin: View {
    @Environment(\.colorScheme) var colorScheme
    @ObservedObject var themeManager = ThemeManager()
    @State var identifica: Int = 0
    @State var usuario: String = ""
    @State var senha: String = ""
    @State private var admin: Bool = false
    @State private var aluno: Bool = false
    @State private var showingAlert = false
    @StateObject var viewModelUsuario = ViewModelUsuario()
    var body: some View {
        NavigationStack{
            ZStack{
                Rectangle()
                    .ignoresSafeArea()
                    .foregroundColor(themeManager.currentTheme == .light ? .amareloHacka : .azulHacka)
                
                VStack{
                    ZStack{
                        Rectangle()
                            .frame(width: 67, height: 37)
                            .cornerRadius(50)
                            .foregroundColor(themeManager.currentTheme == .light ? .azulHacka : .amareloHacka)
                        Button(action: {
                            themeManager.currentTheme = (
                                themeManager.currentTheme == .light ? .dark : .light)
                                        }) {
                                            HStack{
                                                Image(
                                                    systemName:
                                                        themeManager.currentTheme == .light ? "sun.max.circle" : "sun.max")
                                                .resizable()
                                                .scaledToFill()
                                                .frame(width: themeManager.currentTheme == .light ? 25 : 16)
                                                    .foregroundColor(themeManager.currentTheme == .light ? .azulHacka : .amareloHacka)
                                                Image(
                                                    systemName:
                                                        themeManager.currentTheme == .light ? "moon" : "moon.circle")
                                                .resizable()
                                                .scaledToFill()
                                                .frame(width: themeManager.currentTheme == .light ? 16 : 25)
                                                    .foregroundColor(themeManager.currentTheme == .light ? .azulHacka : .amareloHacka)
                                            }
                                            
                                        }
                            .frame(width: 30, height: 1)
                            .padding()
                            .background(themeManager.currentTheme == .light ? .amareloHacka : .azulHacka)
                            .cornerRadius(50)
                    } //botao do tema
                
                    Image(themeManager.currentTheme == .light ? "HackaLogoLight" : "HackaLogoDark")
                        .resizable()
                        .scaledToFit()
                        .frame(width: 300)
                    Spacer()
                    Text("Login:")
                        .font(.headline)
                        .foregroundStyle(themeManager.currentTheme == .light ? .azulHacka : .amareloHacka)
                    TextField("Digite seu login", text: $usuario)
                        .autocorrectionDisabled()
                        .keyboardType(.emailAddress)
                        .textInputAutocapitalization(.never)
                        .frame(width: 300, height: 30)
                        .textFieldStyle(.roundedBorder)
                        .shadow(color: themeManager.currentTheme == .light ? .azulHacka : .amareloHacka, radius: 1, x: 5, y: 5)
                        .padding(.bottom, 30)
                    Text("Senha:")
                        .font(.headline)
                        .foregroundStyle(themeManager.currentTheme == .light ? .azulHacka : .amareloHacka)
                    SecureField("Digite sua senha", text: $senha)
                        .frame(width: 300, height: 30)
                        .textFieldStyle(.roundedBorder)
                        .shadow(color: themeManager.currentTheme == .light ? .azulHacka : .amareloHacka, radius: 1, x: 5, y: 5)
                    Button("Entrar", action: {
                        let teste = autenticaUsu(usu: usuario, pass: senha)
                        if teste == nil{
                            showingAlert = true
                        }
                        else if pegaNivel(ID: teste!)==1{
                            admin = true
                            identifica = teste!
                        }
                        else if pegaNivel(ID: teste!)==2{
                            aluno = true
                            identifica = teste!
                        }
                    })
                    .foregroundColor(.white)
                    .frame(width: 150, height: 40)
                    .background(Color.vermelhoHacka)
                    .cornerRadius(5)
                    .padding()
                    .navigationDestination(isPresented: $admin) {
                        AdminView(usuarioId: identifica)}
                    .navigationDestination(isPresented: $aluno) {
                        UsuarioView(usuarioId: identifica)}
                    .alert(isPresented: $showingAlert) {
                        Alert(title: Text("ALERTA!"),
                              message: Text("Login ou Senha incorretos!"),
                              dismissButton: .default(Text("Voltar!")))
                    }
                    Spacer()
                }
            }
        }
        .navigationBarBackButtonHidden(true)
        .onAppear() {
            viewModelUsuario.fetch()
        }
    }
    
    func autenticaUsu(usu: String, pass: String) -> Int? {
        var idUsu: Int?
        for item in viewModelUsuario.evento {
            if item.status == 1{
                for turma in item.turmas{
                    if turma.status == 1{
                        for usua in turma.usuarios{
                            if usu == usua.email && pass == usua.senha && usua.status == 1{
                                idUsu = usua.id!
                            }
                        }
                    }
                }
            }
        }
        return idUsu
    }
    func pegaNivel(ID: Int) -> Int {
        var nivel: Int = 0
        for item in viewModelUsuario.evento {
            for turma in item.turmas{
                for usua in turma.usuarios{
                    if ID == usua.id{
                        nivel = usua.tipo_usuario!
                    }
                }
            }
        }
        return nivel
    }
}
#Preview {
    telaLogin()
        .environmentObject(PostagemViewModel())
}
