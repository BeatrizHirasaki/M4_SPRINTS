const resultado = document.getElementById('resultado')
const jogarNovamente = document.getElementById('jogar-novamente')

const vitoriasPossiveis = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
]

var quadro = [0, 1, 2, 3, 4, 5, 6, 7, 8]

var jogadorX = []
var jogadorO = []

var jogadoratual = 1

function escolher(espacoQuadro) {
  var espaco = Number(espacoQuadro.id)

  if (quadro.includes(espaco)) {
    if (jogadoratual) {
      espacoQuadro.style.color = 'blue'
      espacoQuadro.innerHTML += 'X'
      jogadorX.push(espaco)
    } else {
      espacoQuadro.style.color = 'red'
      espacoQuadro.innerHTML += 'O'
      jogadorO.push(espaco)
    }

    quadro.splice(quadro.indexOf(espaco), 1)
  }

  if (jogadorX.length + jogadorO.length > 4) {
    if (verificar(jogadorX)) {
      mudarjogo(0, 'X')
    } else if (verificar(jogadorO)) {
      mudarjogo(0, 'O')
    } else if (quadro.length == 0) {
      mudarjogo(1)
    }
  }

  jogadoratual = !jogadoratual
}

function verificar(_jogador) {
  const escolhidos = _jogador

  for (var i = 0; i < vitoriasPossiveis.length; i++) {
    var verificacoes = 0

    for (var j = 0; j < vitoriasPossiveis[i].length; j++) {
      if (escolhidos.includes(vitoriasPossiveis[i][j])) {
        verificacoes++
      }
    }

    if (verificacoes > 2) {
      return true
    }
  }

  return false
}

function mudarjogo(_status, _winner) {
  if (_status == 0) {
    if (_winner == 'X') {
      resultado.style.color = 'blue'
      jogoacabou(1)
    } else {
      resultado.style.color = 'red'
      jogoacabou(2)
    }
    resultado.innerHTML = `${_winner} VENCEU!`
    quadro = []
  } else if (_status == 1) {
    resultado.style.color = 'yellow'
    resultado.innerHTML = 'EMPATE!'
    jogoacabou(3)
  } else {
    quadro = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    jogadorX = []
    jogadorO = []
    for (var i = 0; i < 9; i++) {
      document.getElementById(`${i}`).innerHTML = ''
    }
    resultado.innerHTML = ''
    jogoacabou(0)
  }
}
