
print("\n\t\tEX04\n")


	let shuffledDeck = Deck(mix:false)
    
	let sortedDeck = Deck(mix:true)
    
	var tester : Card?

    print("\n\t********** SORTED DECK **********\n")
    print(sortedDeck.description)
    
    print("\n\t********** SHUFFLED DECK **********\n")
    print(shuffledDeck.description)
    
    for _ in 0..<shuffledDeck.cards.count {
       tester = shuffledDeck.draw()
    }

	tester = nil

    print("\n\t********** After drawing all cards **********")
    print("\t********** Outs Cards **********\n\t")
    print(shuffledDeck.outs)
    
    for card in shuffledDeck.outs {
        shuffledDeck.fold(c:card)
    }
    
    print("\n\t********** After folding all cards **********") 
    print("\t********** Discards Cards **********\n")
    print(shuffledDeck.discards)
