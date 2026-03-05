//
//  Novo_usu.swift
//  TesteAi
//
//  Created by Turma02-2 on 30/07/25.
//

import SwiftUI
import Foundation

struct NovoUsuario: View {
    
    @State var nome = ""
    @State var cpf = ""
    @State var email = ""
    @State var senha = ""
    @Environment(\.dismiss) var dismiss
    var usu = Usuario(id: 0, nome: "", cpf: "", email: "", tipo_usuario: 2,status: 0, senha: "")
    
    @StateObject var view = ViewModelCalendario()
    
    var body: some View {
        
        NavigationView{
            ZStack{
                Color.azulHacka.ignoresSafeArea(.all)
                VStack {
                    
                    Form {
                        
                        Section(header: Text("Nome").foregroundStyle(.amareloHacka)) {
                            TextField("Nome do Usuário", text: $nome)
                                .foregroundStyle(.black)
                            
                        }
                        
                        Section(header: Text("CPF").foregroundStyle(.amareloHacka)) {
                            TextField("CPF do Usuario", text: $cpf)
                                .foregroundStyle(.black)
                            
                        }
                        
                        Section(header: Text("Email").foregroundStyle(.amareloHacka)) {
                            TextField("Email do Usuario", text: $email)
                                .foregroundStyle(.black)
                                .autocorrectionDisabled()
                                .keyboardType(.emailAddress)
                                .textInputAutocapitalization(.never)
                            
                        }
                        
                        Section(header: Text("Senha").foregroundStyle(.amareloHacka)) {
                            TextField("Senha do Usuario", text: $senha)
                                .foregroundStyle(.black)
                                .autocorrectionDisabled()
                                .textInputAutocapitalization(.never)
                            
                        }
                    }
                    
                    Button("Salvar") {
                        if usu.id! > 0{
                            atualiza(novoId: view.usuarios.count+1, Condicao: 2)
                        }
                        else
                        {
                            atualiza(novoId: view.usuarios.count+1, Condicao: 1)
                        }
                        dismiss()
                    }.padding()
                    
                }.scrollContentBackground(.hidden)
                    .background(Color.clear)
                    .transition(.opacity)
            }
        }
        
        .navigationTitle("Detalhes do Evento").foregroundStyle(.amareloHacka)
        .navigationBarTitleDisplayMode(.inline)
        .toolbar {
            ToolbarItem(placement: .navigationBarLeading) {
                Button("Voltar") {
                    dismiss()
                }
            }
        }.onAppear() {
            if usu.id! != 0 {
                nome = usu.nome!
                cpf = usu.cpf!
                senha = usu.senha!
                email = usu.email!
            }
            view.fetch()
        }
    }
    
    func atualiza(novoId: Int, Condicao: Int) {
        for evento in view.evento {
            if evento.status == 1 {
                var TurmaCad: [Turma] = []
                
                for var turma in evento.turmas {
                    if turma.status == 1{
                        var UsuarioAtualizado : [Usuario] = []
                        if Condicao == 1 // insert
                        {
                            
                            for var usuario in turma.usuarios
                            {
                                if usuario.status == 1{
                                    UsuarioAtualizado.append(usuario)
                                }
                            }
                            let usu_novo = Usuario(id: novoId, nome : nome, cpf: cpf, email: email, tipo_usuario: 2, status: 1, senha: senha)
                            UsuarioAtualizado.append(usu_novo)
                        }
                        else //update
                        {
                            for var usuario in turma.usuarios
                            {
                                if usuario.status == 1 && usuario.id == usu.id
                                {
                                    usuario.nome = nome
                                    usuario.cpf = cpf
                                    usuario.email = email
                                    usuario.senha = senha
                                }
                                UsuarioAtualizado.append(usuario)
                            }
                        }
                        turma.usuarios = UsuarioAtualizado
                        TurmaCad.append(turma)
                    }
                    
                }

                let eventoAtualizado = Evento(
                    _id: evento._id,
                    _rev: evento._rev,
                    id: evento.id,
                    nome: evento.nome,
                    status: evento.status,
                    calendario: evento.calendario,
                    turmas: TurmaCad
                )

                view.put(eventoAtualizado)
                print("Evento atualizado enviado:")
                print(eventoAtualizado)
            }
        }
    }
}

#Preview {
    NovoUsuario()
}
