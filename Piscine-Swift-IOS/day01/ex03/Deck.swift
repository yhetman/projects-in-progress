import Foundation

class Deck : NSObject {
	static let allHearts : [Card] = Value.allValues.map {Card(color:Color.Heart, value:$0)}
	static let allClubs : [Card] = Value.allValues.map {Card(color:Color.Club, value:$0)}
	static let allDiamonds : [Card] = Value.allValues.map {Card(color:Color.Diamond, value:$0)}
	static let allSpades : [Card] = Value.allValues.map {Card(color:Color.Spade, value:$0)}
	
	static let allCards : [Card] = allHearts + allClubs + allDiamonds + allSpades
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
