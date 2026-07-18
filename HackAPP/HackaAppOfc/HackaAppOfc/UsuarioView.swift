//
//  ContentView.swift
//  ApiHarryPotter
//
//  Created by Turma02-6 on 14/07/25.
//

import SwiftUI

struct UsuarioView: View {
    @State var usuarioId: Int = 0
    @State var usuarioTipo: Int = 2
    
    var body: some View {
        VStack {
            TabView{
                Avisos()
                    .tabItem{
                        Label("Postagens", systemImage: "newspaper")
                    }
                CalendarView(tipo_usu: usuarioTipo)
                    .tabItem{
                        Label("Calendario", systemImage: "calendar")
                    }
                TirarFotoView(tipoUsuario: usuarioTipo, idusuario: usuarioId)
                    .tabItem{
                        Label("Presença", systemImage: "person.crop.square.badge.camera")
                    }
                MateriaisView()
                    .tabItem{
                        Label("Material", systemImage: "books.vertical")
                    }
                NavigationView{
                    telaLogin()
                }
                .tabItem {
                    Label("Logout", systemImage: "door.right.hand.open")
                }
                .toolbar(.hidden, for: .tabBar)
            }
        }
        .navigationBarBackButtonHidden(true)
    }
}

#Preview {
    UsuarioView()
        .environmentObject(PostagemViewModel())
}

