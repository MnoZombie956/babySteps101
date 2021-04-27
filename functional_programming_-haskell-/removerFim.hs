tamanho :: (Num b) => [a] -> b -- aproveitando uma funcao do primo.hs
tamanho [] = 0
tamanho (_:resto) = 1 + tamanho resto

vaiAtek k _--aproveitando a funcao do shift.hs
  | k <= 0 = []
vaiAtek _ [] = []
vaiAtek k (x:resto) =
  x : vaiAtek (k-1) resto

removerFim n lista =
  vaiAtek (tamanho(lista)-n) lista
  
main = do
  let lista = [1,2,3,4,5,6,7,8,9,10]
  let n=2
  print $ removerFim 7 lista -- n=2 [1,2,3,4]