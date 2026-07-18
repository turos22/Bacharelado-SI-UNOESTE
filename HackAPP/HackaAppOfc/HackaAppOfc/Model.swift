//
//  Model.swift
//  teset11
//
//  Created by Turma02-2 on 14/07/25.
//

import Foundation

struct Evento: Codable, Identifiable, Equatable {
    var _id: String?
    var _rev: String?
    var id: String?
    var nome: String?
    var status: Int?
    var calendario: [Calendario]
    var turmas: [Turma]
}


struct Calendario: Codable, Identifiable, Equatable  {
    var id: Int?
    var data: String? // ou usar Date se desejar com DateFormatter
    var letivo: Int?
    var material_id: String?
    var descricao: String?
    var nome: String?
    var status: Int
}


struct Turma: Codable, Identifiable, Equatable  {
    var id: Int?
    var nome: String?
    var periodo: Int?
    var status: Int
    var usuarios: [Usuario]
    var postagens: [Postagem]
    var materiais: [Material]
    var presencas: [Presenca]
}


struct Usuario: Codable, Identifiable, Equatable  {
    var id: Int?
    var nome: String?
    var cpf: String?
    var email: String?
    var tipo_usuario: Int?
    var status: Int
    var senha: String?
}


struct Postagem: Codable, Identifiable, Equatable  {
    var id: Int
    var titulo: String
    var conteudo: String
    var imagem: String?
    var arquivo: String?
    var link: String?
    var fixado: Int
    var status: Int
}


struct Material: Codable, Identifiable, Equatable, Hashable  {
    var id: Int?
    var nome: String?
    var arquivo: String?
    var link: String?
    var status: Int?
    var grupo: String?
}


struct Presenca: Codable, Identifiable, Equatable{
    var id: Int
    var aluno_id: Int
    var data: String // ou Date com DateFormatter
    var foto: String
}
