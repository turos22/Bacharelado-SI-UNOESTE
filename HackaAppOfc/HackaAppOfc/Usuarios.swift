//
//  Usuarios.swift
//  HackaAppOfc
//
//  Created by Turma02-6 on 30/07/25.
//

import SwiftUI

struct Usuarios: View {
    @StateObject var view = ViewModelCalendario()
    @StateObject var viewModelUsuario = ViewModelUsuario()
    @State private var mostrandoSheetEditar: Bool = false
    @State private var mostrandoSheetNovo: Bool = false
    @State private var mostrarAlertaExclusao = false
    @State private var deletou = false
    @State var usuario_teste = Usuario(id: 0, nome: "", cpf: "", email: "", tipo_usuario: 2,status: 0, senha: "")
    
    var body: some View {
        NavigationStack{
            ZStack{
                Color.azulClaro.ignoresSafeArea()
                ScrollView{
                    VStack{
                        ForEach(view.usuarios){
                            usua in
                            HStack{
                                VStack{
                                    HStack{
                                        Text(usua.nome!)
                                            .font(.headline)
                                        Spacer()
                                    }
                                    HStack{
                                        Text(usua.email!)
                                            .font(.subheadline)
                                        Spacer()
                                    }
                                }
                                .padding()
                                Spacer()
                                Button("Editar"){
                                    mostrandoSheetEditar = true
                                    usuario_teste = usua
                                }
                                .sheet(isPresented: $mostrandoSheetEditar) {
                                    NovoUsuario(usu: usuario_teste).onDisappear {
                                        view.fetch()
                                    }
                                }
                                Button(action:{
                                    usuario_teste = usua
                                    mostrarAlertaExclusao = true
                                    view.fetch()
                                }){
                                    Image(systemName: "xmark.circle.fill")
                                        .resizable()
                                        .scaledToFit()
                                        .frame(width: 30)
                                        .foregroundColor(.red)
                                }
                                .padding()
                                .alert("Confirmar Exclusão", isPresented: $mostrarAlertaExclusao) {
                                    Button("Cancelar", role: .cancel) {}
                                    Button("Excluir", role: .destructive) {
                                        deleta(usuarioD: usuario_teste)
                                        deletou = true
                                    }.navigationDestination(isPresented: $deletou){
                                        Usuarios()
                                    }
                                }
                            }
                            .frame(width: 350, height: 50)
                            .background(Color.amareloHacka)
                            .cornerRadius(10)
                            .shadow(radius: /*@START_MENU_TOKEN@*/10/*@END_MENU_TOKEN@*/)
                            .padding(.leading)
                            .padding(.bottom)
                            .padding(.trailing)
                            
                        }
                        
                    }
                    
                }
                VStack{
                    Spacer()
                    HStack{
                        Spacer()
                        Button(action:{
                            mostrandoSheetEditar = true
                            usuario_teste = Usuario(id: 0, nome: "", cpf: "", email: "", tipo_usuario: 2,status: 0, senha: "")
                        }){
                            Image(systemName: "plus.circle.fill")
                                .resizable()
                                .scaledToFit()
                                .frame(width: 60)
                                .foregroundColor(.azulHacka)
                                .sheet(isPresented: $mostrandoSheetEditar) {
                                    NovoUsuario().onDisappear {
                                        view.fetch()
                                    }
                                }

                        }
                        .padding(30)
                    }
                }
            }
            
        }
        
        .onAppear(){
            view.fetch()
            viewModelUsuario.fetch()
        }
        
    }
    
    
    func deleta(usuarioD: Usuario){
    
        for var evento in view.evento {
            if evento.status == 1 {
                var turmasAtualizadas: [Turma] = []

                for var turma in evento.turmas {
                    if turma.status == 1 {
                        var usuariosAtualizados: [Usuario] = []

                        for var usu in turma.usuarios {
                            if usu != usuarioD {
                                usuariosAtualizados.append(usu)
                            }
    
                        }
                        turma.usuarios = usuariosAtualizados
                        turmasAtualizadas.append(turma)
                    }
                }

                let eventoAtualizado = Evento(
                    _id: evento._id,
                    _rev: evento._rev,
                    id: evento.id,
                    nome: evento.nome,
                    status: evento.status,
                    calendario: evento.calendario,
                    turmas: turmasAtualizadas
                )
                print(turmasAtualizadas)
                viewModelUsuario.put(eventoAtualizado)
                   print("Evento atualizado enviado:")
                   print(eventoAtualizado)
            }
        }

    }
}

#Preview {
    Usuarios()
}
