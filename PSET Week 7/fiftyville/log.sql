-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the duck theft report
SELECT id, year, month, day, street, description
    FROM crime_scene_reports
    WHERE description LIKE "%duck%";

--Find the transcript of the interviews related to the crime
SELECT id, name, year, month, day, transcript
    FROM interviews
    WHERE transcript LIKE "%bakery%";

--What we know at this point, based on the transcripts:
--The bakery is from Emma.The thief withdrewn mony from an ATM in that morning at Legget St, he/she left the bakery within 10 minutes and before hopping on the car, he/she talked to someone else about flight out of the city the next day. The person on the other side of the line is the helper.

-- Crime: 10:15am at Humphrey Street bakery, 2021, 07, 28.
-- Interviews related:
-- 161 Ruth 2021, 07, 28: sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162 Eugene, 2021, 07, 28: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking byt the ATM on legget Street and saw the thief withdrawing some money.
-- 163 Raymond 2021, 07, 28: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- People who withdrew money in the ATM mentioned in the transcripts: Kenny, Iman, Benista, Taylor, Brooke, Luca, Diana, Bruce
SELECT name
    FROM people
    WHERE id IN
        (SELECT person_id
            FROM bank_accounts
            WHERE account_number IN
                (SELECT account_number
                    FROM atm_transactions
                    WHERE year = 2021 and month = 7
                    AND day  = 28
                    AND transaction_type = "withdraw"
                    AND atm_location LIKE "%Legget%"));

-- People who made a call on the day pf the crime, and the call last less then a minute: Kenny, Sofia, Benista, Taylor, Diana, Kelsey, Bruce and Carina
SELECT name
    FROM people
    WHERE phone_number IN
        (SELECT caller
            FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60);

-- Combination of the 2 above to get a combined list of who called and withdrew money on the day of the crime.
-- Updated suspect list: Kenny, Benista, Taylor, Diana and Bruce.
SELECT name
    FROM people
    WHERE id IN
        (SELECT person_id
        FROM bank_accounts
        WHERE account_number IN
            (SELECT account_number
                FROM atm_transactions
                WHERE year = 2021
                AND month = 7
                AND day  = 28
                AND transaction_type = "withdraw"
                AND atm_location LIKE "%Legget%"))
                AND phone_number IN
                    (SELECT caller
                        FROM phone_calls
                        WHERE year = 2021
                        AND month = 7
                        AND day = 28
                        AND duration < 60);

-- Adittion of a 3rd conditional to check from that list, who was caught by the bakery cameras on the day of the crime. Updated list of suspects: Taylor, Diana and Bruce
SELECT id, name, phone_number
    FROM people
    WHERE id IN
        (SELECT person_id
            FROM bank_accounts
            WHERE account_number IN
                (SELECT account_number
                FROM atm_transactions
                WHERE year = 2021
                AND month = 7
                AND day  = 28
                AND transaction_type = "withdraw"
                AND atm_location LIKE "%Legget%"))
            AND phone_number IN
                (SELECT caller
                    FROM phone_calls
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND duration < 60)
            AND license_plate IN
                (SELECT license_plate
                    FROM bakery_security_logs
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND activity = "exit");

-- Received a call from the suspects: Robin, James, and Philip
SELECT people.id, people.name, phone_calls.caller, phone_calls.duration
    FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
        WHERE phone_calls.year = 2021
        AND phone_calls.month = 7
        AND phone_calls.day = 28
        AND phone_calls.duration <60
        AND phone_calls.caller IN
            (SELECT phone_number
                FROM people
                WHERE id IN
                    (SELECT person_id
                        FROM bank_accounts
                        WHERE account_number IN
                            (SELECT account_number
                                FROM atm_transactions
                                WHERE year = 2021
                                AND month = 7
                                AND day  = 28
                                AND transaction_type = "withdraw"
                                AND atm_location LIKE "%Legget%"))
                AND phone_number IN
                    (SELECT caller
                        FROM phone_calls
                        WHERE year = 2021
                        AND month = 7
                        AND day = 28
                        AND duration < 60)
                AND license_plate IN
                    (SELECT license_plate
                        FROM bakery_security_logs
                        WHERE year = 2021
                        AND month = 7
                        AND day = 28
                        AND activity = "exit"));

-- Were in a flight out of Fiftyville on July 29th, 2021
SELECT id, name
    FROM people
    WHERE passport_number IN
        (SELECT passport_number
            FROM passengers
            WHERE flight_id IN
                (SELECT id
                    FROM flights
                    WHERE origin_airport_id =
                        (SELECT id
                            FROM airports
                            WHERE city = "Fiftyville"
                            AND year = 2021
                            AND month = 07
                            AND day = 29) ORDER BY hour ASC))
        AND id IN
            (SELECT person_id
                FROM bank_accounts
                WHERE account_number IN
                    (SELECT account_number
                        FROM atm_transactions
                        WHERE year = 2021
                        AND month = 7
                        AND day  = 28
                        AND transaction_type = "withdraw"
                        AND atm_location LIKE "%Legget%"))
        AND phone_number IN
            (SELECT caller
                FROM phone_calls
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND duration < 60)
        AND license_plate IN
            (SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                AND month = 7
                AND day = 28
                AND activity = "exit");

-- Get flights for suspects on the day after the crime
SELECT *
    FROM flights
    WHERE id IN
        (SELECT flight_id
            FROM passengers
            WHERE passport_number IN
                (SELECT passport_number
                    FROM people
                    WHERE name = "Taylor"
                    OR name = "Diana"
                    OR name = "Bruce"))
    AND month = 7 AND day = 29;

-- Verify the passengers from flight 36. Updated list of suspects: Taylor and Bruce
SELECT name
    FROM people
    WHERE passport_number IN
        (SELECT passport_number
            FROM passengers
            WHERE flight_id = 36);

-- Filter who left the bakery on the day of the crime, the only suspect left: Bruce!
SELECT people.name, people.license_plate, bakery_security_logs.day, bakery_security_logs.hour, bakery_security_logs.minute
    FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE activity = "exit"
    AND hour = 10
    AND day = 28
    AND minute BETWEEN 15 AND 25;


-- Get the ACCOMPLICE: Robin
SELECT people.id, people.name, phone_calls.caller, phone_calls.duration
    FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration <60 AND phone_calls.caller IN
        (SELECT phone_number
            FROM people
            WHERE id =
                (SELECT id
                    FROM people
                    WHERE name = "Bruce"));

-- Final Destination: New York City
SELECT city
    FROM airports
    WHERE id =
        (SELECT destination_airport_id
            FROM flights
            WHERE id = 36);