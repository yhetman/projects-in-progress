
print("\n\t\tEX03\n")
var shuffledDeck = Deck.allCards
var counter = 1

shuffledDeck.shuffle()

print("\tShuffled deck looks like that :")
print("")

for eachCard in shuffledDeck {
	print("| \(counter) | \(eachCard)")
	counter += 1
}
