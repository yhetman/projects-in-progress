import Foundation

class Deck : NSObject {
	
	static let allHearts : [Card] = Value.allValues.map {Card(color : Color.Heart, value : $0)}
	static let allClubs : [Card] = Value.allValues.map {Card(color : Color.Club, value : $0)}
	static let allDiamonds : [Card] = Value.allValues.map {Card(color : Color.Diamond, value : $0)}
	static let allSpades : [Card] = Value.allValues.map {Card(color : Color.Spade, value : $0)}
	
	static let allCards : [Card] = allHearts + allClubs + allDiamonds + allSpades
	
	var cards : [Card] = allCards
	var discards : [Card] = []
	var outs : [Card] = []

	init(mix : Bool) {
		self.cards = Deck.allCards
		if (mix == false) {
			self.cards.shuffle()
			}
		}

	override var description : String {
		var str : String = ""
        for card in self.cards {
			str += "\(card.color) \(card.value) \n"
        }
        return str
	}

	func draw() -> Card? {
        if (self.cards.isEmpty == false) {
            let firstCard = self.cards.first
            outs.append(firstCard!)
            self.cards.removeFirst(1)
            return firstCard
        }
        return nil
    }

	func fold(c : Card) {
        var i = 0
        for eachCard in self.outs {
            if (c == eachCard) {
                self.discards.append(eachCard)
                self.outs.remove(at : i)
            }
            i += 1
        }
    }

}


extension Array {
    mutating func shuffle() {
        for (i, _) in self.enumerated() {
            let newI = Int(arc4random_uniform(UInt32(self.count - 1)))
            let temp = self[i]
            self[i] = self[newI]
            self[newI] = temp
        }
    }
}
