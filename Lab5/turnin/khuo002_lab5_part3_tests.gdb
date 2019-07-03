# Test file for Lab5


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "3 Button Presses => PORTB: 0x07, State = tree"
setPINA 0x00
continue 5
setPINA 0x01
continue 3
setPINA 0x00
expectPORTB 0x07
expect LED_State tree
checkResult

test "2 Button Presses => PORTB: 0x07, State = tree"
setPINA 0x00
continue 5
setPINA 0x01
continue 2
setPINA 0x00
expectPORTB 0x1F
expect LED_State pibuh
checkResult

test "2 Button Presses => PORTB: 0x00, State = ravine"
setPINA 0x00
continue 5
setPINA 0x01
continue 2
setPINA 0x00
expectPORTB 0x00
expect LED_State ravine
checkResult

test "2 Button Presses => PORTB: 0x20, State = sicks"
setPINA 0x00
continue 5
setPINA 0x01
continue 1
setPINA 0x00
expectPORTB 0x20
expect LED_State sicks
checkResult

test "2 Button Presses => PORTB: 0x38, State = FOUR"
setPINA 0x00
continue 5
setPINA 0x01
continue 2
setPINA 0x00
expectPORTB 0x38
expect LED_State FOUR
checkResult

test "3 Button Presses => PORTB: 0x2F, State = juan"
setPINA 0x00
continue 5
setPINA 0x01
continue 3
setPINA 0x00
expectPORTB 0x3F
expect LED_State juan
checkResult

test "1 Button Presses => PORTB: 0x00, State = abyss"
setPINA 0x00
continue 5
setPINA 0x01
continue 1
setPINA 0x00
expectPORTB 0x00
expect LED_State abyss
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
