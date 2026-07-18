//
//  DetalhamentoDia.swift
//  TesteAi
//
//  Created by Turma02-2 on 23/07/25.

import SwiftUI

private var view = ViewModelCalendario()

struct DetalhamentoDia: View {
    var dia = Date()
    @State private var mensagem = "Nada cadastrado no dia"
    @Environment(\.dismiss) var dismiss

    @State private var inativa_exclui : Bool = false
    @State private var isLetivo: Bool = true
    @State private var nome: String = ""
    @State private var descricao: String = ""
    @State private var teste: Material? = nil
    @State var tipousu = 1
    var events = Calendario(id: 0, data: "", letivo: 0, material_id: "", descricao: "", nome: "", status: 0)
    @State private var isStackActive: Bool = false
    @State private var Deletar: Bool = false

    var body: some View {
        NavigationView {
            VStack {
                Text("Eventos em \(dia.formatted(.dateTime.day().month(.wide).year().locale(Locale(identifier: "pt_BR"))))")
                    .font(.title2)
                    .padding(.bottom)
                    .fontWeight(.bold)

                if events.id! < 1 {
                    Text(mensagem)
                        .foregroundColor(.vermelhoHacka.opacity(0.3))
                    VStack {
                        if isStackActive {
                            ZStack{
                                Color.azulHacka.ignoresSafeArea(.all)
                                Form {
                                    Section(header: Text("")) {
                                        Toggle(isOn: $isLetivo) {
                                            Text("Dia Letivo")
                                        }
                                    }
                                    Section(header: Text("Detalhes").foregroundStyle(.amareloHacka)) {
                                        TextField("Nome do Item/Evento", text: $nome)
                                        TextField("Descrição", text: $descricao, axis: .vertical)
                                            .lineLimit(3, reservesSpace: true)
                                    }
                                    Section(header: Text("Material Associado").foregroundStyle(.amareloHacka)) {
                                        Picker("Selecione o Material", selection: $teste) {
                                            Text("Nenhum").tag(nil as Material?)
                                            ForEach(view.materiais) { material in
                                                if let nome = material.nome {
                                                    Text(nome).tag(material as Material?)
                                                }
                                            }
                                        }
                                    }.labelsHidden()
                                }
                                    
                            }.scrollContentBackground(.hidden)
                                .background(Color.clear)
                                .transition(.opacity)
                        }

                        Spacer()
                        HStack {
                            Button(action: {
                                if events.id != 0 {
                                    Deletar = true
                                }
                            }) {
                                Image(systemName: "trash.circle.fill")
                                    .resizable()
                                    .scaledToFit()
                                    .frame(width: 55, height: 55)
                                    .foregroundColor(inativa_exclui ? .vermelhoHacka : .gray)
                            }
                            .clipShape(Circle())
                            .shadow(radius: 10)
                            .opacity(inativa_exclui ? 1.0 : 0.3)

                            Spacer()
                            Button(action: {
                                withAnimation {
                                    isStackActive.toggle()
                                    mensagem = isStackActive ? "" : "Nada cadastrado no dia"
                                }
                            }) {
                                Image(systemName: isStackActive ? "xmark.circle.fill" : "plus.circle.fill")
                                    .resizable()
                                    .scaledToFit()
                                    .frame(width: 55, height: 55)
                                    .foregroundColor(.azulClaro)
                            }
                            .clipShape(Circle())
                            .shadow(radius: 10)
                        }
                        .padding()
                        .disabled(tipousu == 2)
                        .opacity(Double(2 - tipousu))
                    }
                } else {
                    VStack {
                        ZStack{
                            Color.azulHacka.ignoresSafeArea(.all)
                            Form {
                                Section(header: Text("")) {
                                    Toggle(isOn: $isLetivo) {
                                        Text("Dia Letivo")
                                    }
                                }.disabled(tipousu == 2)
                                
                                Section(header: Text("Detalhes").foregroundStyle(.amareloHacka)) {
                                    TextField("Nome do Item/Evento", text: $nome)
                                    TextField("Descrição", text: $descricao, axis: .vertical)
                                        .lineLimit(3, reservesSpace: true)
                                }.disabled(tipousu == 2)
                                
                                Section(header: Text("Material Associado").foregroundStyle(.amareloHacka)) {
                                    Picker("Selecione o Material", selection: $teste) {
                                        Text("Nenhum").tag(nil as Material?)
                                        ForEach(view.materiais) { material in
                                            if let nome = material.nome {
                                                Text(nome).tag(material as Material?)
                                            }
                                        }
                                    }
                                    .disabled(tipousu == 2)
                                    .onChange(of: teste) { novoMaterial in
                                        print("Selecionado: \(String(describing: novoMaterial?.nome))")
                                        
                                    }
                                    .labelsHidden()
                                    
                                }
                            }.transition(.opacity)
                                .background(.azulHacka)
                        }.scrollContentBackground(.hidden)
                            .background(Color.clear)
                            .transition(.opacity)

                        Spacer()

                        HStack {
                            Button(action: {
                                if events.id != 0 {
                                    Deletar = true
                                }
                            }) {
                                Image(systemName: "trash.circle.fill")
                                    .resizable()
                                    .scaledToFit()
                                    .frame(width: 55, height: 55)
                                    .foregroundColor(inativa_exclui ? .vermelhoHacka : .gray)
                            }
                            .clipShape(Circle())
                            .shadow(radius: 10)
                            .opacity(inativa_exclui ? 1.0 : 0.3)

                            Spacer()
                            Text(Deletar ? "Clique em salvar para deletar" : "")
                                .foregroundStyle(Deletar ? .vermelhoHacka : .white)
                            Spacer()
                        }.padding(.leading)
                            .disabled(tipousu == 2)
                            .opacity(Double(2 - tipousu))
                    }
                }

                Button(isStackActive ? "Salvar" : "Fechar") {
                    if Deletar {
                        atualiza(novoId: view.calendarios.count + 1, Condicao: 1)
                    } else {
                        if isStackActive {
                            if events.id == 0 {
                                atualiza(novoId: view.calendarios.count + 1, Condicao: 3)
                            } else {
                                atualiza(novoId: view.calendarios.count + 1, Condicao: 2)
                            }
                        }
                    }
                    dismiss()
                }
                .padding()
            }
            .navigationTitle("Detalhes do Evento")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Button("Done") {
                        dismiss()
                    }
                }
            }
            
        }.onAppear() {
            if events.id! != 0 {
                mensagem = ""
                isLetivo = events.letivo != 0
                nome = events.nome!
                descricao = events.descricao!
                teste = view.materiais.first(where: { String($0.id ?? 0) == events.material_id })
                inativa_exclui = true
                isStackActive = true
            }
            view.fetch()
        }
        
    }

    func atualiza(novoId: Int, Condicao: Int) {
        for evento in view.evento {
            if evento.status == 1 {
                var CalendarioAtualizado: [Calendario] = []

                if Condicao == 1 {
                    for var calendario in evento.calendario {
                        if calendario.status == 1 && calendario.id == events.id {
                            calendario.status = 0
                        }
                        CalendarioAtualizado.append(calendario)
                    }
                } else if Condicao == 2 {
                    for var calendario in evento.calendario {
                        if calendario.status == 1 && calendario.id == events.id {
                            calendario.descricao = descricao
                            calendario.letivo = isLetivo ? 1 : 0
                            calendario.material_id = String(teste?.id ?? 0)
                            calendario.nome = nome
                        }
                        CalendarioAtualizado.append(calendario)
                    }
                } else {
                    for calendario in evento.calendario where calendario.status == 1 {
                        CalendarioAtualizado.append(calendario)
                    }
                    let dateFormatter = DateFormatter()
                    dateFormatter.dateFormat = "yyyy-MM-dd"
                    dateFormatter.locale = Locale(identifier: "en_US_POSIX")
                    let dateString = dateFormatter.string(from: dia)
                    let calendario_novo = Calendario(id: novoId, data: dateString, letivo: isLetivo ? 1 : 0, material_id: String(teste?.id ?? 0), descricao: descricao, nome: nome, status: 1)
                    CalendarioAtualizado.append(calendario_novo)
                }

                let eventoAtualizado = Evento(
                    _id: evento._id,
                    _rev: evento._rev,
                    id: evento.id,
                    nome: evento.nome,
                    status: evento.status,
                    calendario: CalendarioAtualizado,
                    turmas: evento.turmas
                )

                view.put(eventoAtualizado)
                print("Evento atualizado enviado:")
                print(eventoAtualizado)
            }
        }
    }
}

#Preview {
    DetalhamentoDia()
}
