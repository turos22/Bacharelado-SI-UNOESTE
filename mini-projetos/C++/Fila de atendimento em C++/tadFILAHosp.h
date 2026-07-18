#define MAXFILA 50

struct tpElemento{
	int prior, id, tempo;
	char nome[30];
};

struct tpFilaP
{
	int FIM, inicio, qtde;
	tpElemento elem[MAXFILA];
};

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

void Moldura(int CI, int LI, int CF, int LF)
{
	 int a, muda=0;
	 gotoxy(CI,LI);
	 textcolor(4);
	 printf("%c",201);
	 gotoxy(CF,LF);
	 textcolor(7);
	 printf("%c",188);
	 gotoxy(CI,LF);
	 textcolor(4);
	 printf("%c",200);
	 gotoxy(CF,LI);
	 textcolor(7);
	 printf("%c",187);
	 for(a=CI+1; a<CF; a++)
	 {
	 	if(muda==0){
	 		textcolor(4);
	 		muda=1;
	 	}
	 	else{
	 		textcolor(7);
	 		muda=0;
	 	}
		  gotoxy(a,LI);
		  printf("%c",196);
		  gotoxy(a,LF);
		  printf("%c",196);
	 }
	 for(a=LI+1; a<LF; a++)
	 {
	 	if(muda==0){
	 		textcolor(4);
	 		muda=1;
	 	}
	 	else{
	 		textcolor(7);
	 		muda=0;
	 	}
		  gotoxy(CI,a);
		  printf("%c",179);
		  gotoxy(CF,a);
		  printf("%c",179);
	 }
	 textcolor(7);
	 for(a=5; a<8; a++){
	 	for(muda=52;muda<58;muda++){
	 		gotoxy(muda,a);
	 		printf("%c",219);
	 	}
	 }
	 textcolor(4);
	 
	 gotoxy(54,6);
	 printf("%c",219);
	 gotoxy(54,5);
	 printf("%c",219);
	 gotoxy(54,7);
	 printf("%c",219);
	 gotoxy(55,5);
	 printf("%c",219);
	 gotoxy(55,7);
	 printf("%c",219);
	 gotoxy(52,6);
	 printf("%c",219);
	 gotoxy(53,6);
	 printf("%c",219);
	 gotoxy(55,6);
	 printf("%c",219);
	 gotoxy(56,6);
	 printf("%c",219);
	 gotoxy(57,6);
	 printf("%c",219);
	 textcolor(7);
}

void inicializar(tpFilaP &fp)
{
	fp.FIM = -1;
	fp.inicio = 0;
	fp.qtde = 0;
}



void PUSH(tpFilaP &fp, tpElemento paciente)
{
	tpElemento aux;
	int i =0, j=0;
	int remanejo = 1;
	
	if (fp.FIM+1 == MAXFILA)
		fp.FIM = 0;
	else
		fp.FIM++;
		
	fp.elem[fp.FIM] = paciente;

	
	j=fp.FIM;

	for (i = fp.qtde; i>1 && remanejo == 1;i--)
	{
		if (fp.inicio > fp.FIM)
		{
			if (j > 0)
				if (fp.elem[j].prior < fp.elem[j-1].prior)
				{
					aux = fp.elem[j-1];
					fp.elem[j-1] = fp.elem[j];
					fp.elem[j] = aux;
					j--;
				}
				else
					remanejo = 0;
			else
				{
					if (j == 0)
						if(fp.elem[j].prior < fp.elem[MAXFILA-1].prior)
						{
							aux = fp.elem[MAXFILA-1];
							fp.elem[MAXFILA-1] = fp.elem[j];
							fp.elem[j] = aux;
							j = MAXFILA-1;
						}
				   else
				      remanejo = 0;
				}
		}
		else
		{
			if (fp.elem[j].prior < fp.elem[j-1].prior)
				{
					aux = fp.elem[j-1];
					fp.elem[j-1] = fp.elem[j];
					fp.elem[j] = aux;
					j--;
				}
			else
			   remanejo = 0;
		}	
	}
	fp.qtde++;
}




void POP(tpFilaP &fp)
{
	tpElemento elem = fp.elem[fp.inicio];
	fp.qtde--;
	if (fp.inicio +1 == MAXFILA)
		fp.inicio = 0;
	else	
		fp.inicio++;
}

char verifFilaVazia(int qtde)
{
	return qtde == 0;
}

char verifFilaCheia(int qtde)
{
	return qtde == MAXFILA;
}



int elemInicio(tpFilaP fp)
{
	return fp.elem[0].id;
}


void exibirFila(tpFilaP fp, int tempo, int atendimento, int tempoAtend)
{
	int inicio = fp.qtde;
	int tempoExib = tempoAtend%atendimento;
	if(tempoAtend == atendimento)
		tempoExib = atendimento;
	Moldura(26,2,58,8);
	gotoxy(28,5);
	printf("Em atendimento [%d/%d]:", tempoExib,atendimento);
	gotoxy(28,6);
	printf("%d - %s", fp.elem[fp.inicio].id, fp.elem[fp.inicio].nome);
	if (!verifFilaVazia(fp.qtde))
		POP(fp);
	MolduraPadrao(1,1,23,41);
	gotoxy(2,2);
	printf("Fila de pacientes:");
	int xis=4;
	while(!verifFilaVazia(fp.qtde) && inicio-fp.qtde<10){
		gotoxy(2, xis);
		printf("%d - %s", fp.elem[fp.inicio].id, fp.elem[fp.inicio].nome);
		xis++;
		gotoxy(2, xis);
		printf("Prioridade: %d", fp.elem[fp.inicio].prior);
		xis++;
		gotoxy(2, xis);
		printf("Tempo de fila: [%d]", tempo-fp.elem[fp.inicio].tempo);
		POP(fp);
		xis+=2;
	}
	if(inicio-fp.qtde==10){
		gotoxy(2,40);
		printf("...");
	}	
		
}

void Stickman(tpElemento elem){
	int passo=0;
	
	//Abre porta fila
	gotoxy(23,5);
	printf("%c", 197);
	Sleep(100);
	gotoxy(23,5);
	printf(" ");
	gotoxy(23,4);
	printf("%c", 193);
	gotoxy(23,6);
	printf("%c", 194);
	Sleep(100);
	gotoxy(23,4);
	printf(" ");
	gotoxy(23,6);
	printf(" ");
	gotoxy(23,3);
	printf("%c", 193);
	gotoxy(23,7);
	printf("%c", 194);
	
	for(int i=3;i<26;i++){
		gotoxy(i-1,4);
		printf(" ");		
		gotoxy(i-1,5);
		printf(" ");
		gotoxy(i-1,6);
		printf(" ");
		
		gotoxy(i,4);
		switch(passo){
			case 0:
				printf("%c",218);
				break;
			case 1:
				printf("%c",191);
				break;
		}
		gotoxy(i,5);
		printf("%c",219);
		gotoxy(i,6);
		switch(passo){
			case 0:
				printf("%c",217);
				break;
			case 1:
				printf("%c",192);
				break;
		}
		if(passo==0)
			passo=1;
		else
			passo=0;
		Sleep(100);
	}
	
	//Fecha porta fila
	gotoxy(23,3);
	printf("%c", 179);
	gotoxy(23,7);
	printf("%c", 179);
	gotoxy(23,4);
	printf("%c", 193);
	gotoxy(23,6);
	printf("%c", 194);
	Sleep(100);
	gotoxy(23,4);
	printf("%c", 179);
	gotoxy(23,6);
	printf("%c", 179);
	gotoxy(23,5);
	printf("%c", 197);
	Sleep(100);
	gotoxy(23,5);
	printf("%c", 179);
	
	//Abre porta atendimento
	gotoxy(26,5);
	printf("%c", 197);
	Sleep(100);
	gotoxy(26,5);
	printf(" ");
	gotoxy(26,4);
	printf("%c", 193);
	gotoxy(26,6);
	printf("%c", 194);
	Sleep(100);
	gotoxy(26,4);
	printf(" ");
	gotoxy(26,6);
	printf(" ");
	gotoxy(26,3);
	printf("%c", 193);
	gotoxy(26,7);
	printf("%c", 194);
	
	for(int i=25;i<49;i++){
		gotoxy(i-1,4);
		printf(" ");		
		gotoxy(i-1,5);
		printf(" ");
		gotoxy(i-1,6);
		printf(" ");
		
		gotoxy(i,4);
		switch(passo){
			case 0:
				printf("%c",218);
				break;
			case 1:
				printf("%c",191);
				break;
		}
		gotoxy(i,5);
		printf("%c",219);
		gotoxy(i,6);
		switch(passo){
			case 0:
				printf("%c",217);
				break;
			case 1:
				printf("%c",192);
				break;
		}
		if(passo==0)
			passo=1;
		else
			passo=0;
		Sleep(100);
	}
	
	gotoxy(26,3);
	printf("%c", 179);
	gotoxy(26,7);
	printf("%c", 179);
	gotoxy(26,4);
	printf("%c", 193);
	gotoxy(26,6);
	printf("%c", 194);
	Sleep(100);
	gotoxy(26,4);
	printf("%c", 179);
	gotoxy(26,6);
	printf("%c", 179);
	gotoxy(26,5);
	printf("%c", 197);
	Sleep(100);
	gotoxy(26,5);
	printf("%c", 179);
}

void Moldura_Inicio(int x1, int y1,int x2, int y2)
{
	
	int a;
	gotoxy(x1,y1);
	printf("%c",201);
	gotoxy(x2,y1);
	printf("%c",187);
	gotoxy(x1,y2);
	printf("%c",200);
	gotoxy(x2,y2);
	printf("%c",188);
	for(a = x1+1 ;a <x2;a++)
	{
		gotoxy(a,y1);
		printf("%c",205);
	}
	for(a = y1+1 ;a <y2;a++)
	{
		gotoxy(x1,a);
		printf("%c",186);
	}
	for(a = x1+1 ;a <x2;a++)
	{
		gotoxy(a,y2);
		printf("%c",205);
	}
	for(a = y1+1 ;a <y2;a++)
	{
		gotoxy(x2,a);
		printf("%c",186);
	}
}

