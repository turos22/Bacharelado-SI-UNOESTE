
struct Paciente{
	char Class[20],Nome[20],Queixa[20],Data[10];
	int Tempo,prio, tempo_fila;
	Paciente *prox;	
};

struct Descritor{
	int Qtd, tipo;
	// 1 - Veerde
	// 2 - Amarelo
	// 3 - vermelho
	Descritor *prox_desc; // para poder fazer lista de lista
	Paciente *inicio,*fim;
};
//LDDE
struct Medico{
	int Tempo_Estimado,Status, num_sala;
	//Status = 0(Medico indisponivel)
	//status = 1 (medico disponivel)
	int verde_atend, amarelo_atend, vermelho_atend;
	Paciente *atual;
	Medico *ant, *prox;
};

struct DescritorMaster{
	int Qtd;
	Descritor *inicio;
};

struct TpSalasExcluidas
{
	int num_sala, qtd_atend;
};



Medico *New(int num)
{
	Medico *M = new Medico;
    M->Status = 0;
	M->verde_atend=0;
	M->amarelo_atend=0;
	M->vermelho_atend=0;
	M->Tempo_Estimado=0;
	M->ant = M->prox = NULL;
	M->atual = NULL;
	M->num_sala = num;
	return M;
}

Medico *Nova_Sala(int n)
{
	Medico *NO,*aux,*aux2;
	int i;
	
	if(n == 1)
	{
		NO = New(n);
	}else{
		
		NO = New(1);
		//aqui o i começa em 1 pois definimos o no acima.
		for(i = 1 ; i < n ;i++)
		{
			if(i==1)
			{
				aux = New(i+1);
				NO->prox = aux;
				aux->ant = NO;
			}else{
				aux = NO;
				//busca ultimo elemento e conecta o novo a ele.
				while(aux->prox != NULL)
				{
					aux = aux->prox;
				}
				
				aux2 = New(i+1);
				aux->prox = aux2;
				aux2->ant = aux;
			}
		}
	}
	
	//printf("\nsala criada com sucesso!!");
	return NO;
}

Medico *ExcluirFisico(Medico *medicos, TpSalasExcluidas S[100], int &TL, Medico *pos)
{
	int i=0;
	Medico *aux;
	if (pos->ant == NULL)
	{
		//estou na cabeca, no primeiro cara
		S[TL].qtd_atend = pos->amarelo_atend + pos->verde_atend + pos->vermelho_atend;
		S[TL].num_sala = pos->num_sala;
		TL++;
		medicos = pos->prox;
		delete pos;
		
	}
	else if(pos->prox == NULL)
	{
		//estou no ultimo cara
		S[TL].qtd_atend = pos->amarelo_atend + pos->verde_atend + pos->vermelho_atend;
		S[TL].num_sala = pos->num_sala;
		TL++;
		pos->ant->prox = NULL;
		delete pos;
	}
	else
	{
    	//estou no meio de dois
    	S[TL].qtd_atend = pos->amarelo_atend + pos->verde_atend + pos->vermelho_atend;
		S[TL].num_sala = pos->num_sala;
		TL++;
		pos->ant->prox = pos->prox;
		pos->prox->ant = pos->ant;
		delete pos;
	}
	return medicos;
}



void Altera_status_sala(int tipo, Medico *medicos, int num, int inicio, int max_salas)
{ //tipo = 0 remover
  //tipo = 1 INserir
	Medico *aux, *NO;
	int i=0, num_rand, cont_pos, numzin;
	
	
	if (tipo ==1 && inicio == 0)
	{
		for (int y = 0; y<num;y++)
		{
			aux = medicos;
			//adicao de nova sala	
			for(i = 1 ; aux->prox != NULL ;i++)
			{
				aux = aux->prox;
				//chega ate o final
			}
		    numzin = aux->num_sala;
			NO = New(numzin+1);
			NO->Status = 1;
			aux->prox = NO;
			NO->ant = aux;
		}
	}
	else
	{
		
	
	while(i<num)
		{
			num_rand = (rand() % max_salas);
			cont_pos = 0;
			aux = medicos;
			while(cont_pos != num_rand)
			{
				aux=aux->prox;
				cont_pos++;
			} 
			if(aux->Status != tipo)
			{
				aux->Status = tipo;
				i++;
			}
		}
	}
	
	
}


void Inicializar(Descritor &D)
{
	D.Qtd = 0;
	D.inicio = D.fim = NULL;
}

void MolduraPadrao(int CI, int LI, int CF, int LF)
{
 int a;
 gotoxy(CI,LI);
 printf("%c",218);
 gotoxy(CF,LF);
 printf("%c",217);
 gotoxy(CI,LF);
 printf("%c",192);
 gotoxy(CF,LI);
 printf("%c",191);
 for(a=CI+1; a<CF; a++)
 {
  gotoxy(a,LI);
  printf("%c",196);
  gotoxy(a,LF);
  printf("%c",196);
 }
 for(a=LI+1; a<LF; a++)
 {
  gotoxy(CI,a);
  printf("%c",179);
  gotoxy(CF,a);
  printf("%c",179);
 }
}

void Legendas(DescritorMaster D, Medico *M, int verm_atend, int amar_atend, int verd_atend, int temp_verm, int temp_amar, int temp_verd, int temp_geral){
	int x,y,i;
	textcolor(7);
	MolduraPadrao(122,2,162,27);
	gotoxy(138,3);
	printf("LEGENDA");
	gotoxy(124,5);
	printf("Sala ");
	textcolor(4);
	printf("VERMELHA");
	textcolor(7);
	printf(" - Indisponivel");
	gotoxy(124,6);
	printf("Sala ");
	textcolor(2);
	printf("VERDE");
	textcolor(7);
	printf(" - Disponivel");
	
	gotoxy(139,8);
	printf("RESUMO");
	
	gotoxy(124,10);
	printf("Total atendimentos p/ prioridade:");
	gotoxy(124,11);
	textcolor(4);
	printf("Alta ");
	textcolor(7);
	printf(" - %d pacientes", verm_atend);
	gotoxy(124,12);
	textcolor(6);
	printf("Media ");
	textcolor(7);
	printf(" - %d pacientes", amar_atend);
	gotoxy(124,13);
	textcolor(2);
	printf("Baixa ");
	textcolor(7);
	printf(" - %d pacientes", verd_atend);
	
	
	Paciente *aux_vm, *aux_am, *aux_vd;
	Descritor *aux;
	aux_vm = D.inicio->inicio;
	verm_atend += D.inicio->Qtd;
	aux = D.inicio->prox_desc;
	aux_am = aux->inicio;
	amar_atend+=aux->Qtd;
	aux = aux->prox_desc;
	aux_vd = aux->inicio;
	verd_atend+=aux->Qtd;
	
	if(verm_atend == 0)
		verm_atend=1;
	if(amar_atend == 0)
		amar_atend=1;
	if(verd_atend == 0)
		verd_atend=1;
	
	while(aux_vm!=NULL){
		temp_verm += temp_geral - aux_vm->tempo_fila;
		aux_vm = aux_vm->prox;
	}
	while(aux_am!=NULL){
		temp_amar += temp_geral - aux_am->tempo_fila;
		aux_am = aux_am->prox;
	}
	while(aux_vd!=NULL){
		temp_verd += temp_geral - aux_vd->tempo_fila;
		aux_vd = aux_vd->prox;
	}
	gotoxy(124,15);
	printf("Tempo medio de espera p/ prioridade:");
	gotoxy(124,16);
	textcolor(4);
	printf("Alta ");
	textcolor(7);
	printf(" - %d ut", temp_verm/verm_atend);
	gotoxy(124,17);
	textcolor(6);
	printf("Media ");
	textcolor(7);
	printf(" - %d ut", temp_amar/amar_atend);
	gotoxy(124,18);
	textcolor(2);
	printf("Baixa ");
	textcolor(7);
	printf(" - %d ut", temp_verd/verd_atend);
	
	gotoxy(124,20);
	printf("Atendimentos finalizados p/ sala:");
	Medico *m_aux;
	m_aux = M;
	for(y=21;m_aux->prox != NULL;y++){
		int atendimentos = 0;
		atendimentos+= m_aux->vermelho_atend+m_aux->amarelo_atend+m_aux->verde_atend;
		if(m_aux->Status == 0)
			textcolor(4);
		gotoxy(124,y);
		printf("Sala %d ", m_aux->num_sala);
		textcolor(7);
		printf("- %d atendimentos",atendimentos);
		m_aux = m_aux->prox;
	}
}

void Exibir(DescritorMaster D, Medico *M, int verm_atend, int amar_atend, int verd_atend, int temp_verm, int temp_amar, int temp_verd, int temp_geral){
	int x, y, i;
	
	system("cls");
	Legendas(D, M, verm_atend, amar_atend, verd_atend, temp_verm, temp_amar, temp_verd, temp_geral);
	x=y=3;
	MolduraPadrao(1,2,40,12);
	gotoxy(x,y);
	textcolor(4);
	Descritor *aux;
	aux = D.inicio;
	printf("Fila com Prioridade Alta (Total: %d)", aux->Qtd);
	textcolor(7);
	Paciente *aux_p;
	aux_p = aux->inicio;
	for(i=0, y=5;i<6 && aux_p != NULL; i++, y++){
		gotoxy(x,y);
		printf("%s", aux_p->Nome);
		aux_p = aux_p->prox;
	}
	if(aux->Qtd>6){
		gotoxy(x,y);
		printf("...");
	}
	x+=40;
	y=3;
	MolduraPadrao(41,2,80,12);
	gotoxy(x,y);
	textcolor(6);
	aux = aux->prox_desc;
	printf("Fila com Prioridade Media(Total: %d)", aux->Qtd);
	textcolor(7);
	aux_p = aux->inicio;
	for(i=0, y=5;i<6 && aux_p != NULL; i++, y++){
		gotoxy(x,y);
		printf("%s", aux_p->Nome);
		aux_p = aux_p->prox;
	}
	if(aux->Qtd>6){
		gotoxy(x,y);
		printf("...");
	}
	x+=40;
	y=3;
	MolduraPadrao(81,2,120,12);
	gotoxy(x,y);
	textcolor(2);
	aux = aux->prox_desc;
	printf("Fila com Prioridade Baixa(Total: %d)", aux->Qtd);
	textcolor(7);
	aux_p = aux->inicio;
	for(i=0, y=5;i<6 && aux_p != NULL; i++, y++){
		gotoxy(x,y);
		printf("%s", aux_p->Nome);
		aux_p = aux_p->prox;
	}
	if(aux->Qtd>6){
		gotoxy(x,y);
		printf("...");
	}
	gotoxy(50,16);
	printf("SALAS DE ATENDIMENTO");
	Medico *aux_m;
	aux_m = M;
	for(i=0,x=2,y=19; i<3; i++, x+=40){
		if (aux_m != NULL){
			if (aux_m->Status == 0)
			{
				if (aux_m->atual != NULL) //desativado mas em atendimento
				{
					textcolor(4);
					MolduraPadrao(x-1,y-1,x+38,y+3);
					gotoxy(x,y);
					printf("Sala %d", aux_m->num_sala);
					gotoxy(x,y+1);
					printf("Em atendimento: %s", aux_m->atual->Nome);
					gotoxy(x,y+2);
					printf("Tempo de atendimento (%d/%d)", aux_m->Tempo_Estimado, aux_m->atual->Tempo);
					
				}
				else
				{
					//desativado apenas
					textcolor(15);
					MolduraPadrao(x-1,y-1,x+38,y+3);
				}
			}
			else{
				textcolor(2);
				MolduraPadrao(x-1,y-1,x+38,y+3);
				if (aux_m->atual != NULL)
				{
					gotoxy(x,y);
					printf("Sala %d", aux_m->num_sala);
					gotoxy(x,y+1);
					printf("Em atendimento: %s", aux_m->atual->Nome);
					gotoxy(x,y+2);
					printf("Tempo de atendimento (%d/%d)", aux_m->Tempo_Estimado, aux_m->atual->Tempo);
				}
				else
				{				
					gotoxy(x,y);
					printf("Sala %d", aux_m->num_sala);
					gotoxy(x,y+1);
					printf("Sem paciente!");
				}
			}
		}
		else
		{

			textcolor(15);
			MolduraPadrao(x-1,y-1,x+38,y+3);
		}
		
		if (aux_m != NULL)
			aux_m = aux_m->prox;
	}
	for(i=0,x=2,y=24; i<3; i++, x+=40){
		if (aux_m != NULL){
			if (aux_m->Status == 0)
			{
				if (aux_m->atual != NULL) //desativado mas em atendimento
				{
					textcolor(4);
					MolduraPadrao(x-1,y-1,x+38,y+3);
					gotoxy(x,y);
					printf("Sala %d", aux_m->num_sala);
					gotoxy(x,y+1);
					printf("Em atendimento: %s", aux_m->atual->Nome);
					gotoxy(x,y+2);
					printf("Tempo de atendimento (%d/%d)", aux_m->Tempo_Estimado, aux_m->atual->Tempo);
					
				}
				else
				{
					//desativado apenas
					textcolor(15);
					MolduraPadrao(x-1,y-1,x+38,y+3);
				}
			}
			else{
				textcolor(2);
				MolduraPadrao(x-1,y-1,x+38,y+3);
				if (aux_m->atual != NULL)
				{
					gotoxy(x,y);
					printf("Sala %d", aux_m->num_sala);
					gotoxy(x,y+1);
					printf("Em atendimento: %s", aux_m->atual->Nome);
					gotoxy(x,y+2);
					printf("Tempo de atendimento (%d/%d)", aux_m->Tempo_Estimado, aux_m->atual->Tempo);
				}
				else
				{				
					gotoxy(x,y);
					printf("Sala %d", aux_m->num_sala);
					gotoxy(x,y+1);
					printf("Sem paciente!");
				}
			}
		}
		else
		{
			textcolor(15);
			MolduraPadrao(x-1,y-1,x+38,y+3);
		}
		
		if (aux_m != NULL)
			aux_m = aux_m->prox;
	}
	gotoxy(2,28);
	textcolor(7);
	printf("N - Adicionar nova sala          R - Remover sala          ESC - Encerrar programa");
	
	
	gotoxy(x,y);
	
	
	
	
	Sleep(200);
}

Paciente *NovoPaciente(FILE *pont)
{
	Paciente *P = new Paciente;
	int temp_int;
	fscanf(pont,"%[^;];%d;%[^;];%[^;];%[^\n]\n",P->Class,&P->Tempo,P->Nome,P->Queixa,P->Data);
	
	//transforma prioridade em inteiro para facilitar ordenação
	if(strcmp(P->Class, "Vermelho") == 0)
	{
	    P->prio = 1;
	}
	else if(strcmp(P->Class, "Amarelo") == 0)
	{
	    P->prio = 2;
	}
	else
	{
	    P->prio = 3;
	}
	
	P->prox = NULL;		
	return P;
}

Descritor *OrdemPrioritaria(Paciente *Fila,Descritor *D)
{
	Paciente *NO , *ant, *atual;

    if(D->Qtd == 0)
	{
		D->inicio = D->fim = Fila;
		//printf("\n%d", Fila->Tempo);
		//printf("\n%s", Fila->Nome);
	}else
	{
		D->fim->prox = Fila;
		D->fim = Fila;	
	}
	
	D->Qtd++;
	//return Fila;
	return D;
}



void InicializarDescMaster(DescritorMaster &D)
{
	Descritor *aux, *aux1;
    D.Qtd = 3;
    aux = new Descritor;
    aux->Qtd = 0;
    aux->inicio = NULL;
    aux->fim=NULL;
    aux->tipo=1;
    //verde
    D.inicio = aux;
    
    
    aux = new Descritor;
    aux->Qtd = 0;
    aux->inicio = NULL;
    aux->fim=NULL;
    aux->tipo=2;
    //amarelo
    D.inicio->prox_desc = aux;
    
    aux = new Descritor;
    aux->Qtd = 0;
    aux->inicio = NULL;
    aux->fim=NULL;
    aux->tipo=3;
    //vermelho
    aux1 = D.inicio->prox_desc;
    aux1->prox_desc = aux;
}

Paciente *RetornaProxPac(Descritor *D)
{
	Paciente *aux;
	
	if (D->inicio != NULL)
	{
		aux = D->inicio; //cara q vou devolver
		printf("\n%d", aux->Tempo);
		D->inicio = D->inicio ->prox;
		D->Qtd--;
	}
	else
		aux = NULL;
		
	return aux;
}

char ExistePacienteFila(DescritorMaster D)
{
	Descritor *aux_d;
	aux_d = D.inicio->prox_desc;
	return (D.inicio->inicio!=NULL || D.inicio->prox_desc->inicio!=NULL || aux_d->prox_desc->inicio!=NULL);
}


