//
//  AvisosView.swift
//  ApiHarryPotter
//
//  Created by Turma02-6 on 24/07/25.
//

import SwiftUI
import Foundation

struct AvisosView: View {
    @StateObject var viewModelUsuario = ViewModelUsuario()
    @State var novoIdInt: Int = 4
    
    var body: some View {
        Button("Postar",action: {
            atualiza(novoId: novoIdInt)
        })
        .onAppear() {
            viewModelUsuario.fetch()
        }
    }
    
    func atualiza(novoId: Int){
    
        for var evento in viewModelUsuario.evento {
            if evento.status == 1 {
                var turmasAtualizadas: [Turma] = []

                for var turma in evento.turmas {
                    if turma.status == 1 {
                        var usuariosAtualizados: [Usuario] = []

                        for var usu in turma.usuarios {
                            if usu.status == 1 && usu.id == 4 {
                                usu.id = novoId
                                usu.nome = "VAAAAAAI"
                            }
                            usuariosAtualizados.append(usu)
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

                viewModelUsuario.put(eventoAtualizado)
                   print("Evento atualizado enviado:")
                   print(eventoAtualizado)
            }
        }

    }
}

#Preview {
    AvisosView()
}
