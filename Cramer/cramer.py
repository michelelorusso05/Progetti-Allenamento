import tkinter as tk

def strEquationToArray(equationString):
	minusOccurrencies = equationString.find("- ")

	while minusOccurrencies != -1:
		equationString = equationString[:minusOccurrencies+1] + equationString[minusOccurrencies+2:]
		minusOccurrencies = equationString.find("- ")

	equationString = equationString.replace("=", "").replace("+", "").split()
	return equationString

def equationArrayToIntArray(equationArray):
	coefficients = []

	for i in range(len(equationArray)):
		equationArray[i] = equationArray[i].replace("x", "").replace("y", "")
		if len(equationArray[i]) == 0 or (equationArray[i].find("-") != -1 and len(equationArray[i]) == 1):
			equationArray[i] += "1"
		coefficients.append(eval(equationArray[i]))
	return coefficients

def resolveCramer(coefficientsFirst, coefficientsSecond):
	delta = (coefficientsFirst[0] * coefficientsSecond[1]) - (coefficientsSecond[0] * coefficientsFirst[1])
	deltaX = (coefficientsFirst[2] * coefficientsSecond[1]) - (coefficientsSecond[2] * coefficientsFirst[1])
	deltaY = (coefficientsFirst[0] * coefficientsSecond[2]) - (coefficientsSecond[0] * coefficientsFirst[2])

	x = deltaX / delta
	y = deltaY / delta

	return (x, y)

def formatResult(x):
	# Python 3.6+ required

	xStr = ""
	if x.is_integer():
		xStr = str(round(x))
	else:
		xStr = f"{x.as_integer_ratio()[0]}/{x.as_integer_ratio()[1]}"
	return xStr

def buttonSolve(rStr, label):
	primaEquazione_strArray = firstEquationVar.get()
	secondaEquazione_strArray = secondEquationVar.get()

	primaEquazione_strArray = strEquationToArray(primaEquazione_strArray)
	secondaEquazione_strArray = strEquationToArray(secondaEquazione_strArray)

	coefficientiPrimo = equationArrayToIntArray(primaEquazione_strArray)
	coefficientiSecondo = equationArrayToIntArray(secondaEquazione_strArray)

	result = resolveCramer(coefficientiPrimo, coefficientiSecondo)
	rStr.set(f"La soluzione è: ({formatResult(result[0])}, {formatResult(result[1])})")
	label["text"] = rStr.get()
	root.update_idletasks()

if __name__ == "__main__":
	root = tk.Tk()
	root.title("Equazioni con Cramer")
	root.geometry("500x150")
	root.resizable(False, False)

	firstEquationVar = tk.StringVar()
	entry = tk.Entry(root, textvariable=firstEquationVar).pack(padx=20, pady=10, ipadx=100, ipady=3)

	secondEquationVar = tk.StringVar()
	entry2 = tk.Entry(root, textvariable=secondEquationVar).pack(padx=20, pady=0, ipadx=100, ipady=3)

	parenthesis = tk.Label(root, text="{", font=("Arial", 46)).place(x=30, y=0)

	resultStr = tk.StringVar()
	resultStr.set("Pronto")
	resultLabel = tk.Label(root, text=resultStr.get())
	resultLabel.pack(side=tk.BOTTOM, pady=10)

	button = tk.Button(root, text="Risolvi", command=lambda: buttonSolve(resultStr, resultLabel)).pack(pady=5)

	root.mainloop()
