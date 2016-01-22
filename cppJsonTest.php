<?php

$array = array("FirstName" => "John", "LastName" => "Doe", "Age" => 43, "Address" => array("Street" => "Downing Street 10", "City" => "London", "Country" => "Great Britain"), "Phone number" => "+44 1234567" );

exit(json_encode($array));

?>

<!--
{
    "FirstName": "John",
    "LastName": "Doe",
    "Age": 43,
    "Address": {
        "Street": "Downing Street 10",
        "City": "London",
        "Country": "Great Britain"
    },
    "Phone number": "+44 1234567"
}
-->