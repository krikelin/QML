# QML
QML is a simple semantic markup Language, that supports marking up text flow with properties.
 It's special ambition is to be a **lightweight**, cool and nice markup language. The key features is:

 * Simple to make parsers, very few special tokens.
 * Twitter-compatibility. The feature is to easy render trees of twitter mentions
 
# Example:

				The #book w with the #title "QML Language specs", written in the small ¤city Lidköping by the @author Alexander #describes about the new cool #language QML,
 
# Element
 A element tag is beginning with a #<element Name>, containing the text and is ended with a '.'. The choice of sign is to make it fast to type on all kind of keyboards,
 even smaller on laptops. Elements can contain nested elements. Here is a book element
 
				#Book
					#Title QML Documentation
				.
 
## Arrays
A set of items should not use the same #tag at the same time, instead it should be clocked together into a array separated by a','. The reason to do this
is that it will be easier to implement the parses and faster processing.

					#Book(
						#Title QML Documentation.
					,
						#Title XML vs. QML
					.
	
## Types
Types is preceeding with special tokens, to make it easier for developers to create implementations.

List of token declarations:

 * Strings "" or raw data
				
				#Element
					#Title a
		
 * Date and time
				
				#element
					~Pubdate 2011-03-16
		
 * Numbers
				#element
					$number 221
 * Float

				#element
					%altitude 4.444
 * Price
			
			#item
					%Price £436
			
 * Authors/People
***Important: Authors tokens is putted before the value, not replacing the tag to fit the twitter tags.***
					
					#book
						#author @param
						
But it can also be shortened into this

					#book
						@jonas
 * Date and time
 
				#element
					~Pubdate 2011-03-16
				
				