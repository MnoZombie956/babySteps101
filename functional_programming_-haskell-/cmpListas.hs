data ListaT = Sublista | Superlista | Identica | Invalida
  deriving (Show, Eq)

tamanho :: (Num b) => [a] -> b
tamanho [] = 0
tamanho (_:resto) = 1 + tamanho resto

vaiAtek k _--para consertar o non exhaustive parameters
  | k <= 0 = []
vaiAtek _ [] = []
vaiAtek k (x:resto) =
  x : vaiAtek (k-1) resto

cmpSuper [] (y:ys)  = Invalida
cmpSuper (x:xs) (y:ys)
  | x == y && (vaiAtek (tamanho ([y]++ys)) ([x]++xs))==([y]++ys) = Superlista
  | otherwise = cmpSuper (xs) ([y]++ys) 
  
cmpSub (x:xs) [] = Invalida
cmpSub (x:xs) (y:ys)
  | x == y && (vaiAtek (tamanho ([x]++xs)) ([y]++ys))==([x]++xs) = Sublista
  | otherwise = cmpSub ([x]++xs) (ys)
  
cmpListas :: [Integer] -> [Integer] -> ListaT
cmpListas [] [] = Identica
cmpListas [] (y:ys) = Invalida
cmpListas (x:xs) [] = Invalida
cmpListas [_] [] = Invalida
cmpListas [] [_] = Invalida
cmpListas (x:xs) (y:ys) 
  | (tamanho xs > tamanho ys) = cmpSuper (x:xs) (y:ys) 
  | (tamanho xs < tamanho ys) = cmpSub (x:xs) (y:ys) 
  | otherwise = if (x==y) && (xs==ys) then Identica else Invalida 

main = do
  print(cmpListas  [12,3,4] [])