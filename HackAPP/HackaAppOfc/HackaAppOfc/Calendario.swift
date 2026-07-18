import SwiftUI
import Foundation


struct CalendarView: View {
    @State private var color: Color = .blue
    @State private var date = Date.now
    let daysOfWeek = Date.capitalizedFirstLettersOfWeekdays
    let columns = Array(repeating: GridItem(.flexible()), count: 7)
    @State private var days: [Date] = []
    @State var tipo_usu : Int = 0

    @State private var showingEventSheet = false

    @State private var selectedEvent: Evento?

    @State private var eventsForSelectedDay: Calendario = Calendario(id: 0, data: "", letivo: 0, material_id: "", descricao: "", nome: "", status: 0)
    @State private var diaEvento : Date = Date()
    @StateObject var view = ViewModelCalendario()
    @State private var showPicker = false


    private let eventDateFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = "dd/MM/yyyy"
        formatter.locale = Locale(identifier: "pt_BR")
        formatter.calendar = Calendar(identifier: .gregorian)
        return formatter
    }()

    var body: some View {
        ZStack{
            ZStack {
                LinearGradient(
                    gradient: Gradient(colors: [Color.azulHacka, Color.vermelhoHacka]),
                    startPoint: .center,
                    endPoint: .bottomTrailing
                )
                .edgesIgnoringSafeArea(.top)

                ForEach(0..<80, id: \.self) { _ in
                    Circle()
                        .fill(Color.white.opacity(Double.random(in: 0.2...0.6)))
                        .frame(width: CGFloat.random(in: 1...3), height: CGFloat.random(in: 1...3))
                        .position(
                            x: CGFloat.random(in: 0...UIScreen.main.bounds.width),
                            y: CGFloat.random(in: 0...UIScreen.main.bounds.height)
                        )
                }
            }
            VStack {
                
                
                
                LabeledContent("Data e Hora") {
                    Button {
                        showPicker = true
                    } label: {
                        Text(date.formatted(date: .abbreviated, time: .omitted))
                    }
                    .foregroundColor(.amareloHacka) // <- agora funciona 100%
                    .sheet(isPresented: $showPicker) {
                        VStack {
                            DatePicker("Selecione a data", selection: $date, displayedComponents: [.date, .hourAndMinute])
                                .datePickerStyle(.graphical)
                                .tint(.amareloHacka)
                                .padding()
                            Button("Fechar") {
                                showPicker = false
                            }
                            .padding()
                        }
                    }
                }
                .padding(.bottom)
                .foregroundStyle(.amareloHacka)
                
                
                HStack {
                    ForEach(daysOfWeek.indices, id: \.self) { index in
                        VStack(spacing: 4) {
                            Text(daysOfWeek[index])
                                .font(.subheadline)
                                .fontWeight(.black)
                                .foregroundStyle(.amareloHacka)
                                .frame(maxWidth: .infinity)
                            
                            Color.clear.frame(height: 6)
                        }
                    }
                }
                
                
                LazyVGrid(columns: columns) {
                    ForEach(days, id: \.self) { day in
                        
                        if day.monthInt != date.monthInt {
                            Color.clear
                                .frame(maxWidth: .infinity, minHeight: 40)
                        } else {
                            
                            Button {
                                
                                let events = getEvents(for: day)
                                if events != nil {
                                    self.eventsForSelectedDay = events!
                                    
                                    self.showingEventSheet = true
                                } else {
                                    self.showingEventSheet = true
                                    self.eventsForSelectedDay = Calendario(id: 0, data: "", letivo: 0, material_id: "", descricao: "", nome: "", status: 0)
                                }
                                diaEvento = day
                                
                            } label: {
                                VStack(spacing: 3) {
                                    Text(day.formatted(.dateTime.day()))
                                        .fontWeight(.black )
                                        .foregroundStyle(.secondary)
                                        .frame(maxWidth: .infinity, minHeight: 40)
                                        .background(
                                            Circle()
                                                .foregroundStyle(
                                                    
                                                    Date.now.startOfDay == day.startOfDay
                                                    ? .amareloHacka.opacity(0.8)
                                                    : dialetivo(for: day)
                                                    ? .green.opacity(0.8)
                                                    :.azulClaro.opacity(0.8)
                                                )
                                        ).foregroundStyle(Date.now.startOfDay == day.startOfDay
                                                          ? .vermelhoHacka
                                                          : dialetivo(for: day)
                                                          ? .black
                                                          :.azulHacka)
                                    
                                    Circle()
                                        .fill(hasEvent(for: day) ? .white : .clear)
                                        .frame(width: 6, height: 6)
                                }
                            }
                            .buttonStyle(.plain)
                        }
                    }
                }
            }
            .padding()
            .onAppear {
                days = date.calendarDisplayDays
                view.fetch()
            }
            .onChange(of: date) {
                days = date.calendarDisplayDays
            }
            .sheet(isPresented: $showingEventSheet) {
                DetalhamentoDia(dia: diaEvento, tipousu: tipo_usu,events: eventsForSelectedDay)
                    .onDisappear {
                        view.fetch()
                    }
                
            }
        }
    }

    func hasEvent(for day: Date) -> Bool {
        let formatter = DateFormatter()
            formatter.dateFormat = "yyyy-MM-dd"
            formatter.locale = Locale(identifier: "en_US_POSIX") // padrão para formatos fixos

            return view.calendarios.contains { element in
                if let dateString = element.data,
                   let eventDate = formatter.date(from: dateString){
                    if element.status == 1{
                        return Calendar.current.isDate(eventDate, inSameDayAs: day)
                    }
                   return false
                }
                return false
            }
    }
    
    func dialetivo(for day: Date) -> Bool {
        let formatter = DateFormatter()
            formatter.dateFormat = "yyyy-MM-dd"
            formatter.locale = Locale(identifier: "en_US_POSIX") // padrão para formatos fixos

            return view.calendarios.contains { element in
                if let dateString = element.data,
                   let eventDate = formatter.date(from: dateString){
                    if element.letivo == 0 && element.status==1{
                        return Calendar.current.isDate(eventDate, inSameDayAs: day)
                    }
                    return false
                }
                return false
            }
    }

    func getEvents(for day: Date) -> Calendario? {
        let formatter = DateFormatter()
            formatter.dateFormat = "yyyy-MM-dd"
            formatter.locale = Locale(identifier: "en_US_POSIX") // padrão para formatos fixos

        return view.calendarios.first { element in
            if let dateString = element.data,
               let eventDate = formatter.date(from: dateString)  {
                if element.status == 1{
                    return Calendar.current.isDate(eventDate, inSameDayAs: day)
                }
                else
                {
                    return false
                }
               
            }
            return false
        }
    }

}



#Preview {
    CalendarView()
}
