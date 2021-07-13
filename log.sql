-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- declaration of witnesses
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;

-- the thief withdraw some money
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type LIKE "withdraw";

-- INFO ABOUT people who withdrew
SELECT name, phone_number, passport_number, license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type LIKE "withdraw"));

-- see who left the parking lot in that timeframe
SELECT license_plate, hour, minute FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <=25 AND activity = "exit";

-- see the name of those who left
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <=25 AND activity = "exit");

-- see calls from the ones that left the courthouse and are suspects (WHO THRY CALLED)
SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Elizabeth" OR name = "Danielle" OR name = "Russell" OR name = "Ernest");

-- test each of the 4 suspects and see who they called
SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Elizabeth");
SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Danielle");
SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Russell");
-- RUSSEL called ... (see name)
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Russell"));
-- RUSSEL CALLED PHILIP

-- ERNEST CALLED BERTHOLD
SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest");
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));

-- see flights from Fiftyville on the 29th
SELECT id, destination_airport_id, hour, minute FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND month = 7 AND day = 29;

-- search for the two suspects on each of the flights tomorrow
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 43);
