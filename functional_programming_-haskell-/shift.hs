vaiAtek k _--para consertar o non exhaustive parameters
  | k <= 0 = []
vaiAtek _ [] = []
vaiAtek k (x:resto) =
  x : vaiAtek (k-1) resto

kAteFim k resto--msm coisa
  | k <= 0 =  resto
kAteFim _ [] =[]
kAteFim k (_:lista) =  
  kAteFim (k-1) lista

shift :: Int -> [a] -> [a]
shift _ [] = []
shift qnt lista =
	kAteFim qnt lista ++ vaiAtek qnt lista
	
main = do
  let lista = [1,5,6,7,3,4,1]
  print $ shift 3 lista 
