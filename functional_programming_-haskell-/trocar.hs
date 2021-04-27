trocar :: Int -> [Int]
trocar 0 = []
trocar valor
	| valor >= 100 = trocar (valor-100) ++ [100]  
	| valor >= 50 = trocar (valor-50) ++ [50] 
	| valor >= 10 = trocar (valor-10) ++ [10]
	| valor >= 5 = trocar (valor-5) ++ [5]
	| valor >= 1 = trocar (valor-1) ++ [1]

main = do
	let valor = 199 -- -> [1,1,1,1,5,10,10,10,10,50,100]
	print $ trocar valor -- 162 -> [1, 1, 10, 50, 100]
