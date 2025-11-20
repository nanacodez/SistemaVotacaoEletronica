// aguarda o html ser carregado antes de executar o script
document.addEventListener('DOMContentLoaded', () => {

    // database
    let db_eleitores = [];
    let db_candidatos = [];

    // contadores de votos
    let totalVotosNulos = 0;
    let totalVotosBrancos = 0;
    let eleitorVotando = null; // guarda o eleitor autenticado

    // funcoes utilitarias
    // mapeamento de todas as "telas" (divs)
    const telas = {
        menu: document.getElementById('tela-menu'),
        cadastroEleitor: document.getElementById('tela-cadastro-eleitor'),
        cadastroCandidato: document.getElementById('tela-cadastro-candidato'),
        votacao: document.getElementById('tela-votacao'),
        apuracao: document.getElementById('tela-apuracao')
    };

    // mapeamento das etapas da votacao
    const etapaVotacao1 = document.getElementById('etapa-votacao-1');
    const etapaVotacao2 = document.getElementById('etapa-votacao-2');

    // mapeamento dos formularios
    const formCadastroEleitor = document.getElementById('form-cadastro-eleitor');
    const formCadastroCandidato = document.getElementById('form-cadastro-candidato');
    const formAutenticarEleitor = document.getElementById('form-autenticar-eleitor');
    
    // mapeamento dos botoes
    const botoesVoltar = document.querySelectorAll('.btn-voltar');
    const btnIrCadastroEleitor = document.getElementById('btn-ir-cadastrar-eleitor');
    const btnIrCadastroCandidato = document.getElementById('btn-ir-cadastrar-candidato');
    const btnIrVotacao = document.getElementById('btn-ir-votacao');
    const btnIrApuracao = document.getElementById('btn-ir-apuracao');
    const btnConfirmarVoto = document.getElementById('btn-confirmar-voto');

    /** 
     * funcao para navegar entre as telas (substitui o switch-case do main.c)
     * @param {string} idTela O ID da tela para mostrar (ex: 'menu')
     */

    function mostrarTela(idTela) {
        // esconde todas as telas
        Object.values(telas).forEach(tela => tela.hidden = true);
        
        // limpa formularios ao voltar ao menu
        if (idTela === 'menu') {
            formCadastroEleitor.reset();
            formCadastroCandidato.reset();
            formAutenticarEleitor.reset();
            
            // reseta as etapas da votacao
            etapaVotacao1.hidden = false;
            etapaVotacao2.hidden = true;
            eleitorVotando = null;
            document.getElementById('voto-numero').value = '';

            // atualiza contadores do menu
            atualizarContadoresMenu();
        }

        // mostra a tela desejada
        telas[idTela].hidden = false;
    }

    /*
     * atualiza os contadores na tela de menu
     * equivalente a 'db_getTotalEleitores()' e 'db_getTotalCandidatos()'
     */

    function atualizarContadoresMenu() {
        document.getElementById('total-eleitores').textContent = db_eleitores.length;
        document.getElementById('total-candidatos').textContent = db_candidatos.length;
    }

    //navegacao do menu principal
    // botoes para ir para as telas de cadastro
    btnIrCadastroEleitor.addEventListener('click', () => mostrarTela('cadastroEleitor'));
    btnIrCadastroCandidato.addEventListener('click', () => mostrarTela('cadastroCandidato'));
    btnIrVotacao.addEventListener('click', () => mostrarTela('votacao'));
    
    // botoes de "voltar"
    botoesVoltar.forEach(btn => btn.addEventListener('click', () => mostrarTela('menu')));

    // botao para ir para a apuracao (precisa executar a logica ANTES)
    btnIrApuracao.addEventListener('click', () => {
        executarApuracao(); // executa a logica de contagem
        mostrarTela('apuracao'); // mostra a tela de resultados
    });

    //funcoes de cadastro do eleitor
    formCadastroEleitor.addEventListener('submit', (evento) => {
        evento.preventDefault(); // impede o recarregamento da pagina

        // coleta dados do formulario
        const nome = document.getElementById('eleitor-nome').value;
        const idade = parseInt(document.getElementById('eleitor-idade').value);
        const titulo = document.getElementById('eleitor-titulo').value;

        // validacoes
        if (idade < 16) {
            alert('!! ERRO: Idade mínima para votar é 16 anos.');
            return;
        }
        if (titulo.length !== 12 || !/^\d+$/.test(titulo)) {
            alert('!! ERRO: O título deve ter exatamente 12 dígitos numéricos.');
            return;
        }
        if (db_eleitores.find(e => e.titulo === titulo)) {
            alert('!! ERRO: Este título de eleitor já está cadastrado.');
            return;
        }
        // fim das validacoes

        // adiciona ao banco de dados
        db_eleitores.push({ nome, idade, titulo, jaVotou: false });

        alert('>> SUCESSO: Eleitor cadastrado.');
        mostrarTela('menu'); // volta ao menu
    });

    //funcoes de cadastro do candidato

    formCadastroCandidato.addEventListener('submit', (evento) => {
        evento.preventDefault();

        const nome = document.getElementById('candidato-nome').value;
        const partido = document.getElementById('candidato-partido').value;
        const numero = document.getElementById('candidato-numero').value;

        // validacoes
        if (numero.length !== 5 || !/^\d+$/.test(numero)) {
            alert('!! ERRO: O número do candidato deve ter 5 dígitos numéricos.');
            return;
        }
        if (db_candidatos.find(c => c.numero === numero)) {
            alert('!! ERRO: Este número de candidato já está cadastrado.');
            return;
        }
        // fim das validacoes

        // adiciona ao "banco de dados"
        db_candidatos.push({ nome, partido, numero, votosRecebidos: 0 });
        
        alert('>> SUCESSO: Candidato cadastrado.');
        mostrarTela('menu'); // volta ao menu
    });


    //funcao votacao
     
    // autenticacao
    formAutenticarEleitor.addEventListener('submit', (evento) => {
        evento.preventDefault();
        const titulo = document.getElementById('voto-titulo').value;
        
        const eleitor = db_eleitores.find(e => e.titulo === titulo);

        if (!eleitor) {
            alert('!! ERRO: Eleitor não cadastrado no sistema.');
            return;
        }
        if (eleitor.jaVotou) {
            alert('!! ATENÇÃO: O eleitor "' + eleitor.nome + '" já votou.');
            return;
        }

        // sucesso na autenticacao
        eleitorVotando = eleitor; // guarda o eleitor que esta votando
        document.getElementById('nome-eleitor-votando').textContent = eleitor.nome;
        
        // avanca para a etapa 2
        etapaVotacao1.hidden = true;
        etapaVotacao2.hidden = false;
    });

    // confirmacao do voto
    btnConfirmarVoto.addEventListener('click', () => {
        const voto = document.getElementById('voto-numero').value.toUpperCase();

        // voto em branco
        if (voto === 'BRANCO') {
            // 'confirm' eh o 'confirmarVoto(s/n)' do c
            if (confirm('Confirmar voto EM BRANCO?')) {
                totalVotosBrancos++;
                eleitorVotando.jaVotou = true;
                alert('>> Voto EM BRANCO registrado com sucesso!');
                mostrarTela('menu');
            }
        }
        // voto em candidato
        else {
            const candidato = db_candidatos.find(c => c.numero === voto);
            
            // voto nulo (candidato nao existe)
            if (!candidato) {
                if (confirm('!! Número de candidato inválido.\nConfirmar voto NULO?')) {
                    totalVotosNulos++;
                    eleitorVotando.jaVotou = true;
                    alert('>> Voto NULO registrado com sucesso!');
                    mostrarTela('menu');
                }
            }
            // voto valido
            else {
                const mensagem = `--- Você está votando em: ---\nNome: ${candidato.nome}\nPartido: ${candidato.partido}\n\nConfirmar voto?`;
                if (confirm(mensagem)) {
                    candidato.votosRecebidos++;
                    eleitorVotando.jaVotou = true;
                    alert('>> Voto VÁLIDO registrado com sucesso!');
                    mostrarTela('menu');
                }
            }
        }
    });

    //funcao da apuracao
    function executarApuracao() {
        
        // limpa resultados anteriores
        const divResultados = document.getElementById('resultados-candidatos');
        divResultados.innerHTML = '';
        
        // ordena os candidatos
        // '...' cria uma cópia para nao ordenar o "banco" original
        const resultadosOrdenados = [...db_candidatos].sort((a, b) => b.votosRecebidos - a.votosRecebidos);

        // exibe os candidatos ordenados
        if (resultadosOrdenados.length === 0) {
            divResultados.innerHTML = '<p>Nenhum candidato cadastrado.</p>';
        } else {
            resultadosOrdenados.forEach((candidato, index) => {
                divResultados.innerHTML += `<p>${index + 1}. ${candidato.nome} (${candidato.partido}) - <strong>${candidato.votosRecebidos} votos</strong></p>`;
            });
        }
        
        // exibe votos brancos e nulos
        document.getElementById('total-brancos').textContent = totalVotosBrancos;
        document.getElementById('total-nulos').textContent = totalVotosNulos;

        // correcao e integridade final
        const eleitoresQueVotaram = db_eleitores.filter(e => e.jaVotou).length;
        const totalVotosValidos = db_candidatos.reduce((soma, c) => soma + c.votosRecebidos, 0);
        const totalVotosUrna = totalVotosValidos + totalVotosBrancos + totalVotosNulos;
        
        document.getElementById('total-votantes').textContent = eleitoresQueVotaram;
        document.getElementById('total-votos-urna').textContent = totalVotosUrna;

        const auditoria = document.getElementById('resultado-auditoria');
        if (eleitoresQueVotaram === totalVotosUrna) {
            auditoria.textContent = '>> SUCESSO: A contagem de votos bate com o número de votantes.';
            auditoria.style.color = 'green';
        } else {
            auditoria.textContent = `!! FALHA DE INTEGRIDADE: Contagem de votos (${totalVotosUrna}) e votantes (${eleitoresQueVotaram}) DIVERGENTE!`;
            auditoria.style.color = 'red';
        }
    }

    // inicializacao ---
    // inicia o app mostrando o menu e atualizando os contadores
    mostrarTela('menu');

}); 
// fim do 'DOMContentLoaded'