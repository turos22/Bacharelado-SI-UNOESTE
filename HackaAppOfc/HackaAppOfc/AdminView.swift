import SwiftUI

struct AdminView: View {
    
    @State var usuarioId: Int = 0
    @State var usuarioTipo: Int = 1
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
                        Label("Presenças", systemImage: "chart.pie")
                    }
                MateriaisADMView()
                    .tabItem{
                        Label("Material", systemImage: "books.vertical")
                    }
                ConfigView()
                    .tabItem{
                        Label("Config.", systemImage: "gearshape.fill")
                    }
            }
        }
        .navigationBarBackButtonHidden(true)
    }
}

#Preview {
    AdminView()
        .environmentObject(PostagemViewModel())
}
