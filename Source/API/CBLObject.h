//
//  CBLObject.h
//  CouchbaseLite
//
//  Created by Jens Alfke on 8/15/14.
//
//

#import <Foundation/Foundation.h>


/** Base class for objects with persistence, i.e. that have Objective-C properties that map to
    JSON object properties, and can track what properties have changed in memory.
    Persistent properties are defined by using CBLSynthesize() or CBLSynthesizeAs() in the subclass
    @implementation block. */
@interface CBLObject : NSObject

/** The object's persistent properties in JSON-compatible form.
    The property value omits keys for persistent properties that have 0/false/nil values;
    this is more efficient for storage and parsing.
    Setting this property resets the values of _all_ persistent properties; any that don't have
    a corresponding value in the NSDictionary will be reset to 0/false/nil. */
@property (copy) NSDictionary* persistentProperties;

/** Writes all dirty persistent properties to the `properties` dictionary.
    Returns YES if `properties` was changed as a result. */
- (BOOL) getPersistentPropertiesInto: (NSMutableDictionary*)properties;

/** YES if any property setters have been called.
    This flag is set automatically the first time any persistent property setter is called.
    This flag is cleared automatically when the .persistentProperties property is set. */
@property (readonly, nonatomic) BOOL needsSave;



@property (readonly, nonatomic) BOOL isFault;

// protected:
- (void) awokeFromFault;

@end


// Used inside a CBLObject subclass's @implementation to define a persistent property.
#define CBLSynthesize(PROP)            @synthesize PROP= _doc_##PROP

// Used inside a subclass's @implementation to define a persistent property with a custom JSON
// property name (which must still be a valid identifier: "Foo_Bar" is OK but not "Foo Bar".)
#define CBLSynthesizeAs(PROP, JSONPROP) @synthesize PROP= _doc_##JSONPROP
