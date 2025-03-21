In this branch :

1. **Factory Classes**:
   - Created `EasyCritterFactory`, `MediumCritterFactory`, and `HardCritterFactory` classes, each responsible for creating critters with specific attributes.
   - These factories encapsulate the logic for setting critter attributes (e.g., hitpoints, reward, speed) based on the wave number.

2. **CritterGroupGenerator**:
   - Updated `CritterGroupGenerator` to use the appropriate factory based on the wave number:
     - Waves 1–3: `EasyCritterFactory`
     - Waves 4–6: `MediumCritterFactory`
     - Waves 7+: `HardCritterFactory`
   - Removed manual critter attribute initialization and replaced it with factory-based creation.

3. **Benefits**:
   - Improved modularity: Critter creation logic is now encapsulated in separate factory classes.
   - Scalability: Adding new critter types or modifying existing ones is easier and does not require changes to the `CritterGroupGenerator`.
   - Consistency: Critter attributes are consistent across all critters of the same type.

4. **Testing**:
   - Tested critter generation for waves 1, 4, and 7 to ensure correct factory selection and critter attributes.
   - Verified that critters are properly initialized with their positions at the entry point.
  
Also, - raw pointers were used in `CritterGroupGenerator` to manage an array of `Critter` objects.
- Memory for the critter array was allocated dynamically using `new Critter[numCritters]`.
- Responsibility for deallocating memory was handled manually using `delete[]` to avoid memory leaks.
- Raw pointers were chosen for simplicity and compatibility with the existing codebase.
