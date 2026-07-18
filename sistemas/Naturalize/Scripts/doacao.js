document.addEventListener('DOMContentLoaded', function() {
    const formaPagamentoRadios = document.querySelectorAll('input[name="forma_pagamento"]');
    const valorMudar = document.querySelectorAll('input[name="valor"]');
    const divCartao = document.getElementById('div_cartao');
    const divPix = document.getElementById('div_pix');
    const qrcode = document.getElementById('qrcode');
    const valor = document.getElementById('valor');
    

    formaPagamentoRadios.forEach(radio => {
        radio.addEventListener('change', function() {
            if(divPix) divPix.style.display = 'none';
            if(divCartao) divCartao.style.display = 'none';
            if (this.value === 'pix') {
                divPix.style.display = 'flex';
                qrcode.src = `https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=${valor.value}`;
            } else if (this.value === 'credito' || this.value === 'debito') {
                divCartao.style.display = 'flex';
                qrcode.src = '';
            }
        });
    });

    valorMudar.forEach(input => {
        input.addEventListener('change', function() {
            if (document.querySelector('input[name="forma_pagamento"]:checked')?.value === 'pix') {
                qrcode.src = `https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=${this.value}`;
            }
        });
    });

    
});