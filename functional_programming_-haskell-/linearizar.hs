linearizar [] = []
linearizar (xs:xss) = [x | x <- xs]++linearizar(xss)

main = do
	let listas1 = [ [1,2], [5], [0,4,2] ]
	print(linearizar listas1)

