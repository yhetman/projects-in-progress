import Foundation

class Card : NSObject {

	var color : Color
	var value : Value
	
	init(color:Color, value:Value) {
		self.value = value
		self.color = color
		super.init()
	}
	
	override var description:String {
		let str = "color : \(self.color), value : \(self.value.rawValue)"
		return str
    }
    
    override func isEqual(to object: Any?) -> Bool {
        if let obj = object as? Card {
            return (obj.color == self.color && obj.value == self.value)
        }
        return false
    }
}

func ==(first: Card, second: Card) -> Bool {
    return (first.color == second.color && first.value == second.value)
}
