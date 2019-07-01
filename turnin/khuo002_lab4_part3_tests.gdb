# Test file for LabFOUR


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

#Testing Direct Key W/ State Zero
test "PINA: 0x00 => PORTB: 0x00, state: Zero"
setPINA 0x00
continue 3
expectPORTB 0x00
expect Lock_State Zero

#Testing Direct Key W/ State Two
test "PINA: 0x01 => PORTB: 0x00, state: Four"
setPINA 0x01
continue 3
setPINA 0x00
continue 3
expectPORTB 0x00
expect Lock_State Four

#Testing Direct Key W/ State Four
test "PINA: 0x02 => PORTB: 0x01, state: Five"
setPINA 0x02
continue 3
setPINA 0x00
continue 2
expectPORTB 0x01
expect Lock_State Five

#Testing Lock
test "PINA: 0x80 => PORTB: 0x00, state: Zero"
setPINA 0x80
continue 3
setPINA 0x00
continue 3
expectPORTB 0x00
expect Lock_State Zero

#Testing Incorrect Button
test "PINA: 0x02 => PORTB: 0x00, State: Two"
setPINA 0x02
continue 3
expectPORTB 0x00
expect Lock_State Two


test "PINA: 0x04 => PORTB: 0x00, State: Four"
setPINA 0x00
continue 5
setPINA 0x04
continue 3
expectPORTB 0x00
expect Lock_State Three

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
