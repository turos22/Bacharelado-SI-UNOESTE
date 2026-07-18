const bolinhas = document.getElementById('bolinhas');
const botaodrop = document.getElementById('dropdownMenuButton1');
const labelpadrao = document.getElementById('lbl');
const entradapadrao = document.getElementById('entrada');
const resp = document.getElementById('resp');
const textarea = document.getElementById('textarea');
const resultado = document.getElementById('resultado');
const dropdownfundo = document.getElementById('dropdownFundo');
const resposta_label = document.getElementById('resposta_label');
const incremento = document.getElementById('incremento');
const numero_alvo = document.querySelector('.numero_alvo');

var exercicio = 1;
var lista = [];
var cronometro_iniciado = 0;

function alterarfundo(num)
{
    const sol = document.getElementById('sol');
    const lua = document.getElementById('lua');

    if (num == 1 && sol.classList.contains('active')) {
       return;
    }

    if (num == 2 && lua.classList.contains('active')) {
        return;
    }
    sol.classList.remove('active');
    lua.classList.remove('active');

    let cor1 = '#F8F8F2';
    let cor2 = '#00FFFF';
    num = parseInt(num);
    switch(num)
    {
        case 1:
            cor2 = 'black';
            sol.classList.add('active');
            break;
        case 2:
            lua.classList.add('active');
            cor1 = 'black';
            break;
        case 3:
            cor1 = 'blue';
            cor2 = 'white';
            break;
        case 4:
            cor1 = 'green';
            cor2 = 'white';
            break;
        case 5:
            cor1 = 'purple';
            cor2 = 'white';
            break;
    }

    document.getElementsByTagName('section')[0].style.backgroundColor = cor1;
    bolinhas.querySelectorAll('div').forEach(bolinha => {
        bolinha.style.backgroundColor = cor2;
    });
}

function criarBolinhas() {
    for (let i = 0; i < 50; i++) {
        const bolinha = document.createElement('div');
        bolinha.classList.add('bolinha');
        bolinha.style.left = Math.random() * 100 + "%";
        bolinha.style.top = Math.random() * 100 + "%";
        bolinha.style.width = Math.random() * 10 + 10 + "px";
        bolinha.style.height = bolinha.style.width
        bolinha.style.animationDuration = Math.random() * 1 + 5 + "s";
        let animacao = Math.floor(Math.random() * 4) + 1;
        switch (animacao) {
            case 1:
                bolinha.style.animationName = "esquerda";
                bolinha.style.boxShadow = "10px 0px 15px rgba(0,255,255,0.5)"
                break;
            case 2:
                bolinha.style.animationName = "direita";
                bolinha.style.boxShadow = "-10px 0px 15px rgba(0,255,255,0.5)"
                break;
            case 3:
                bolinha.style.animationName = "cima";
                bolinha.style.boxShadow = "0px 10px 15px rgba(0,255,255,0.5)"
                break;
            case 4:
                bolinha.style.animationName = "baixo";
                bolinha.style.boxShadow = "0px -10px 15px rgba(0,255,255,0.5)"
                break;
        }
        bolinhas.appendChild(bolinha);
    }

}


function alterarexercicio(num)
{  entradapadrao.value = '';
    textarea.value = '';
    textarea.style.display = 'none';
    numero_alvo.innerText = '0';

    if (document.getElementById('incremento').style.display == 'block')    {
        document.getElementById('incremento').style.display = 'none';
        numero_alvo.innerText = '0';
    }

    if (document.getElementById('cronometro').style.display == 'flex')    {
        document.getElementById('cronometro').style.display = 'none';
        document.getElementById('botoes_cronometro').style.display = 'none';
        clearInterval(cronometro_intervalo);
        cronometro_iniciado = 0;
        min_crono.innerText = '00';
        seg_crono.innerText = '00';
    }

    if (document.getElementById('cadastro').style.display == 'block') {
        document.getElementById('cadastro').style.display = 'none';
        const nome = document.getElementById('nome');
        const email = document.getElementById('email');
        const cpf = document.getElementById('cpf');
        const celular = document.getElementById('celular');
        nome.value = '';
        email.value = '';
        cpf.value = '';
        celular.value = '';
    }

    labelpadrao.style.display = 'block';
    entradapadrao.style.display = 'block';
    resultado.style.display = 'block';
    resposta_label.style.display = 'block';
    resp.style.display = 'block';
    resultado.innerText = '';
    lista = [];
    switch(num)
    {
        case 1:
            labelpadrao.innerText = 'Texto';
            entradapadrao.placeholder = 'Digite o Palavra a inverter...';
            botaodrop.innerText = 'Inverter Palavra';
            resp.innerText = 'Inverter';
            exercicio = 1;
            break;
        
        case 2:
            labelpadrao.innerText = 'Texto';
            entradapadrao.placeholder = 'Digite o texto a inverter...';
            entradapadrao.style.display = 'none';
            textarea.style.display = 'block';
            botaodrop.innerText = 'Inverter Texto';
            resp.innerText = 'Inverter';
            exercicio = 2;
            break;

        case 3:
            labelpadrao.innerText = 'Palavra';
            entradapadrao.placeholder = 'Digite o Palavra a guardar...';
            botaodrop.innerText = 'Guardar Palavra';
            resp.innerText = 'Guardar';
            exercicio = 3;
            break;
        
        case 4:
            labelpadrao.innerText = 'Palavra';
            entradapadrao.placeholder = 'Digite o Palavra a remover vogais...';
            botaodrop.innerText = 'Remover Vogais';
            resp.innerText = 'Remover Vogais';
            exercicio = 4;
            break;
        
        case 5:
            labelpadrao.innerText = 'Salário';
            entradapadrao.placeholder = 'Digite o salário...';
            botaodrop.innerText = 'Calcular Salário';
            resp.innerText = 'Calcular Salário';
            exercicio = 5;
            break;

        case 6:
            labelpadrao.style.display = 'none';
            entradapadrao.style.display = 'none';
            resultado.style.display = 'none';
            resposta_label.style.display = 'none';
            botaodrop.innerText = 'Incrementar';
            resp.style.display = 'none';
            incremento.style.display = 'block';
            exercicio = 6;
            break;
        
        case 7:
            labelpadrao.style.display = 'none';
            entradapadrao.style.display = 'none';
            resultado.style.display = 'none';
            resposta_label.style.display = 'none';
            botaodrop.innerText = 'Incrementar';
            resp.style.display = 'none';
            document.getElementById('cronometro').style.display = 'flex';
            document.getElementById('botoes_cronometro').style.display = 'flex';
            exercicio = 7;
            break;
        
        case 8:
            labelpadrao.style.display = 'none';
            entradapadrao.style.display = 'none';
            resultado.style.display = 'none';
            resposta_label.style.display = 'none';
            botaodrop.innerText = 'Validar Cadastro';
            resp.style.display = 'none';
            document.getElementById('cadastro').style.display = 'block';
            exercicio = 8;
            break;
    }
}

function gerarresultado()
{
    resultado.innerText = '';
    let i = 0;
    console.log(exercicio);
    switch(exercicio)
    {
        case 1:
            for (i = entradapadrao.value.length-1; i >= 0; i--) {
                resultado.innerText += entradapadrao.value[i];   
            }
            break;
        case 2:
            let palavras = textarea.value.trim().split(/\s+/); 
            resultado.textContent = palavras.reverse().join(' ');
            break;
        case 3:
            i = 0
            while (i < lista.length && lista[i].toUpperCase() != entradapadrao.value.toUpperCase())
                i++;
            if (i == lista.length)
            {
                lista.push(entradapadrao.value);
            }
            else
            {
                alert('Palavra ja guardada');
            }
            resultado.innerText = lista;
            break;
        case 4:
            let textosemvogal = entradapadrao.value.replace(/[aeiouáâàãéêíóôõúAÁÂÀÃÉÊÍÓÔÕÚ]/gi, '');
            resultado.innerText = textosemvogal;
            break;
        case 5:
            let salario = parseFloat(entradapadrao.value);
            let salario_resultado = 0;
            console.log(salario);
            if (salario <= 1621.00) {
                salario_resultado = salario - (salario * 0.075);
            } else if (salario <= 2902.84) {
                salario_resultado = salario - (salario * 0.09 - 24.32);
            } else if (salario <= 4354.27) {
                salario_resultado = salario - (salario * 0.12 - 111.40);
            } else {
                salario_resultado = salario - (salario * 0.14 - 198.49);
            }
            console.log(salario_resultado);

            if (salario > 2259.20){
                if (salario <= 2826.65) {
                salario_resultado = salario_resultado - (salario * 0.075 - 169.44);
                } else if (salario <= 3751.05) {
                    salario_resultado = salario_resultado - (salario * 0.15 - 381.44);
                } else if (salario <= 4664.68) {
                    salario_resultado = salario_resultado - (salario * 0.225 - 662.77);
                } else {
                    salario_resultado = salario_resultado - (salario * 0.275 - 896.00);
                }
            }
            console.log(salario_resultado);
            resultado.innerText = salario_resultado;
            break;
    }   
}

function incrementar(valor){
    let numero_atual = parseInt(numero_alvo.innerText);
    numero_atual += valor;
    numero_alvo.innerText = numero_atual;

    if (numero_atual % 2 == 0)
        numero_alvo.style.color = 'lightblue';
    else
        numero_alvo.style.color = 'green';    
}

const min_crono = document.getElementById('min_crono');
const seg_crono = document.getElementById('seg_crono');
var segundos = 0;
var minutos = 0;
var cronometro_intervalo;
function iniciarCronometro() {
    if(!cronometro_iniciado){
        cronometro_iniciado = 1;
        segundos = 0;
        minutos = 0;
    }

    cronometro_intervalo = setInterval(() => {
        segundos++;
        if (segundos == 60) {
            minutos++;
            segundos = 0;
        }

        if (minutos < 10)
            min_crono.innerText = '0' + minutos.toString();
        else
            min_crono.innerText = minutos.toString();

        if (segundos < 10)
            seg_crono.innerText = '0' + segundos.toString();
        else
            seg_crono.innerText = segundos.toString();
    }, 1000);
}

function pararCronometro() {
    clearInterval(cronometro_intervalo);
    cronometro_iniciado = 0;
}

function resetarCronometro() {
    clearInterval(cronometro_intervalo);
    cronometro_iniciado = 0;
    min_crono.innerText = '00';
    seg_crono.innerText = '00';
}

function validarCadastro(){
    const cadastro = document.getElementById('cadastro');
    const nome = document.getElementById('nome');
    const email = document.getElementById('email');
    const cpf = document.getElementById('cpf');
    const celular = document.getElementById('celular');

    let erros = '';

    if (nome.value == '' || email.value == '' || cpf.value == '' || celular.value == '') {
        alert('Preencha todos os campos');
        return false;
    }

    if (nome.value.split(' ').length < 2) 
        erros += 'O nome deve conter pelo menos 2 palavras\n';


    if (email.value.indexOf('@') == -1)
        erros += 'O email deve conter @\n';

    

    if ( cpf.value.length != 11)
        erros += 'O CPF deve conter 11 dígitos\n';

    if (celular.value.length < 8 || celular.value.length > 9)
        erros += 'O celular deve conter entre 8 e 9 dígitos\n';


    if (erros != '') {
        alert(erros);
        return false;
    }
    else   {
        alert('Cadastro válido!!');
        return true;
    }
}

criarBolinhas();
alterarexercicio(exercicio);