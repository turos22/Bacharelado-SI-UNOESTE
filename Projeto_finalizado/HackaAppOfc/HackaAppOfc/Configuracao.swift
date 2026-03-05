import SwiftUI

struct Configuracao: View {
    @StateObject var viewModel = PostagemViewModel()
    @State private var mostrarSheet = false
    
    var body: some View {
        VStack(spacing: 20) {
            Text("Configurações")
                .font(.largeTitle)
            
            Button("Gerenciar Postagens") {
                mostrarSheet = true
            }
            .sheet(isPresented: $mostrarSheet) {
                SheetPostagensView()
            }
        }
        .padding()
        .onAppear(){
            viewModel.fetch()
        }
    }
}

struct SheetPostagensView: View {
    @StateObject var viewModel = PostagemViewModel()
    @State private var postagemParaEditar: Postagem?
    @State private var postagemParaExcluir: Postagem?
    @State private var mostrarAlertaExclusao = false
    @State private var mostrarNovaPostagem = false
    
    var body: some View {
        NavigationView {
            List {
                ForEach(viewModel.postagens.filter { $0.status == 1 }) { postagem in
                    VStack(alignment: .leading, spacing: 8) {
                        Text(postagem.titulo).font(.headline)
                        Text(postagem.conteudo).font(.subheadline)
                        
                        HStack {
                            Button(action: {
                                postagemParaEditar = postagem
                            }) {
                                Text("Alterar")
                                    .padding(8)
                                    .background(Color.blue)
                                    .foregroundColor(.white)
                                    .cornerRadius(8)
                            }
                            .buttonStyle(PlainButtonStyle())
                            
                            Button(action: {
                                postagemParaExcluir = postagem
                                mostrarAlertaExclusao = true
                            }) {
                                Text("Excluir")
                                    .padding(8)
                                    .background(Color.red)
                                    .foregroundColor(.white)
                                    .cornerRadius(8)
                            }
                            .buttonStyle(PlainButtonStyle())
                            
                            Button(action: {
                                viewModel.fixarPostagem(id: postagem.id)
                            }) {
                                Text(postagem.fixado == 1 ? "Desfixar" : "Fixar")
                                    .padding(8)
                                    .background(Color.orange)
                                    .foregroundColor(.white)
                                    .cornerRadius(8)
                            }
                            .buttonStyle(PlainButtonStyle())
                        }
                        .font(.footnote)
                    }
                    .padding(.vertical, 8)
                }
            }
            .navigationTitle("Postagens")
            .alert("Confirmar Exclusão", isPresented: $mostrarAlertaExclusao) {
                Button("Cancelar", role: .cancel) {}
                Button("Excluir", role: .destructive) {
                    if let postagem = postagemParaExcluir {
                        viewModel.excluirLogicamente(id: postagem.id)
                    }
                }
            } message: {
                Text("Tem certeza que deseja excluir esta postagem?")
            }
            .sheet(item: $postagemParaEditar) { postagem in
                EditarPostagemView(postagem: postagem) { novoTitulo, novoConteudo in
                    viewModel.editarPostagem(id: postagem.id, novoTitulo: novoTitulo, novoConteudo: novoConteudo)
                }
            }
            .navigationTitle("Postagens")
                        .toolbar {
                            ToolbarItem(placement: .primaryAction) {
                                Button(action: {
                                    mostrarNovaPostagem = true
                                }) {
                                    Image(systemName: "plus")
                                        .font(.headline)
                                }
                            }
                        }
                        .sheet(isPresented: $mostrarNovaPostagem) {
                            NovaPostagemView()
                        }
        }
        .onAppear(){
            viewModel.fetch()
        }
    }
        
}

struct EditarPostagemView: View {
    var postagem: Postagem
    var onSalvar: (_ titulo: String, _ conteudo: String) -> Void

    @Environment(\.dismiss) var dismiss
    @State private var novoTitulo: String
    @State private var novoConteudo: String

    init(postagem: Postagem, onSalvar: @escaping (_ titulo: String, _ conteudo: String) -> Void) {
        self.postagem = postagem
        self.onSalvar = onSalvar
        self._novoTitulo = State(initialValue: postagem.titulo)
        self._novoConteudo = State(initialValue: postagem.conteudo)
    }
    
    var body: some View {
        NavigationView {
            Form {
                Section(header: Text("Título")) {
                    TextField("Título", text: $novoTitulo)
                }

                Section(header: Text("Conteúdo")) {
                    TextEditor(text: $novoConteudo)
                        .frame(minHeight: 100)
                }
            }
            .navigationTitle("Editar Postagem")
            .toolbar {
                ToolbarItem(placement: .confirmationAction) {
                    Button("Salvar") {
                        onSalvar(novoTitulo, novoConteudo)
                        dismiss()
                    }
                    .disabled(novoTitulo.isEmpty || novoConteudo.isEmpty)
                }

                ToolbarItem(placement: .cancellationAction) {
                    Button("Cancelar") {
                        dismiss()
                    }
                }
            }
        }
        
    }
}

struct NovaPostagemView: View {
    @StateObject var viewModel = PostagemViewModel()
    @Environment(\.dismiss) var dismiss
    
    @State private var novoTitulo: String = ""
    @State private var novoConteudo: String = ""
    @State private var novaImagem: String = ""
    @State private var novoArquivo: String = ""
    @State private var novoLink: String = ""
    
    var body: some View {
        NavigationStack {
            Form {
                Section(header: Text("Informações Básicas")) {
                    TextField("Título", text: $novoTitulo)
                    TextEditor(text: $novoConteudo)
                        .frame(minHeight: 100)
                }
                
                Section(header: Text("Mídia")) {
                    TextField("URL da Imagem (opcional)", text: $novaImagem)
                    TextField("Nome do Arquivo (opcional)", text: $novoArquivo)
                    TextField("URL do Link (opcional)", text: $novoLink)
                }
            }
            .navigationTitle("Nova Postagem")
            .toolbar {
                /*
                ToolbarItem(placement: .cancellationAction) {
                    Button {
                        dismiss()
                    } label: {
                        Text("Cancelar")
                    }
                }
                */
                
                ToolbarItem(placement: .confirmationAction) {
                    Button("Salvar") {
                        let novaPostagem = Postagem(
                            id: 0,
                            titulo: novoTitulo,
                            conteudo: novoConteudo,
                            imagem: novaImagem.isEmpty ? nil : novaImagem,
                            arquivo: novoArquivo.isEmpty ? nil : novoArquivo,
                            link: novoLink.isEmpty ? nil : novoLink,
                            fixado: 0,
                            status: 1
                        )
                        viewModel.adicionarPostagem(postagem: novaPostagem)
                        dismiss()
                    }
                    .disabled(novoTitulo.isEmpty || novoConteudo.isEmpty)
                }
            }
        }
        .onAppear(){
            viewModel.fetch()
        }
    }
}

#Preview {
    Configuracao()
        .environmentObject(PostagemViewModel())
}
