<!DOCTYPE html>
<html>
<head>
	<title>Coffee Machine</title>
    <link rel="stylesheet" type="text/css" href="index.css">
</head>

<?php
        $servername = "localhost";
        $username = "timodebimo_admin";
        $password = "Koffie1";
        $dbname = "timodebimo_coffeemaker";

        //Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        //Check connection
        if($conn->connect_error){
            die("Connection failed: " . $conn->connect_error);
        }

        $sql = "SELECT * FROM Drinks";
        $result = $conn->query($sql); 
        $coffee = $result->fetch_assoc()["Coffee"];

        $sql = "SELECT * FROM Drinks";
        $result = $conn->query($sql); 
        $choccymilk = $result->fetch_assoc()["ChocolateMilk"];

        $sql = "SELECT * FROM Drinks";
        $result = $conn->query($sql); 
        $tea = $result->fetch_assoc()["Coffee"];

    ?>

<body>
	<div>
		<button type="button" id="makeCoffee" class="button">Make Coffee</button>
		<button type="button" id="makeChocolateMilk" class="button">Make Chocolate Milk</button>
		<button type="button" id="makeTea" class="button">Make Tea</button>
	</div>
    <div>
        <label type="hidden" id="coffeeCount"><?php echo $coffee?></label>
        <label type="hidden" id="chocolateCount"><?php echo $choccymilk?></label>
        <label type="hidden" id="teaCount"><?php echo $tea?></label>
    </div>
	<!--<div class="add-message">
        <input type="text" id="tbAddMessage" placeholder="Message here"/>
        <button type="button" id="btnAddMessage">Publish</button>
    </div>-->

    <p id="messages" class="messages"></p>

    <div id="chartContainer" style="height: 370px; width: 50%;"></div>

    <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>

	<script src="https://mqtt.fhict.nl/cdn/paho.javascript-1.0.1/mqttws31-min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/1.12.3/jquery.min.js"></script>
    <script type="text/javascript">
        // Documentation found at http://www.eclipse.org/paho/clients/js/
        // or http://www.eclipse.org/paho/files/jsdoc/index.html

        var tempmessage = "";
        var chart;

        var tea = document.getElementById('teaCount').innerHTML;
        var chocolateMilk = document.getElementById('chocolateCount').innerHTML;
        var coffee= document.getElementById('coffeeCount').innerHTML;
        var total = 0;

        var connection = true;

        // Create a client (host,port,unique client id)
        client = new Paho.MQTT.Client("mqtt.fhict.nl", 8884, (Math.random() * 1e32).toString(36));
        // set callback handlers
        client.onConnectionLost = onConnectionLost;
        client.onMessageArrived = onMessageArrived;

        // connect the client
        client.connect({
            onSuccess: onConnect,
            onFailure: onFailure,
            useSSL: true,
            userName: "i339762_martijnbooij",
            password: "Rtd1Ss44uHGLNq"
        });


        // called when the client connects
        function onConnect() 
        {
            // Once a connection has been made, make a subscription and send a message.
            console.log("onConnect");

            //Subscribe to the topic we want to listen to (same as the one we are sending data too.)
            client.subscribe("public/i339762_martijnbooij/");
        }

        function onFailure(responseObject)
        {
          console.log("onFailure: ",responseObject);
        }

        // called when the client loses its connection
        function onConnectionLost(responseObject) 
        {
            if (responseObject.errorCode !== 0) 
            {
                console.log("onConnectionLost:" + responseObject.errorMessage);

                connection = false;
            }
        }

        // called when a message arrives
        function onMessageArrived(message)
        {
            console.log("onMessageArrived:" + message.payloadString);
            console.log(message);

            if (tempmessage != message.payloadString)
            {
                // You could filter all the messages here, we just accept everything (and do some html encoding).
                //$('#messages').append($('<li>').text(message.payloadString));
                //$('#messages').update(message.payloadString);
                document.getElementById('messages').innerHTML = "Latest message: " + message.payloadString;

                tempmessage = message.payloadString;
            }
        }

        // OnReady
        $(document).ready(function() {
            // Add click handler
            $('#makeCoffee').click(function() {
                // Create new message with the text
                message = new Paho.MQTT.Message("makeCoffee");
                message.destinationName = "public/i339762_martijnbooij/";
                // Send the message
                client.send(message);

                document.getElementById('coffeeCount').innerHTML = parseInt(document.getElementById('coffeeCount').innerHTML) + 1;

                UpdateBarGraph();
            });

            $('#makeChocolateMilk').click(function() {
                // Create new message with the text
                message = new Paho.MQTT.Message("makeChocolateMilk");
                message.destinationName = "public/i339762_martijnbooij/";
                // Send the message
                client.send(message);

                document.getElementById('chocolateCount').innerHTML = parseInt(document.getElementById('chocolateCount').innerHTML) + 1;

                UpdateBarGraph();
            });

            $('#makeTea').click(function() {
                // Create new message with the text
                message = new Paho.MQTT.Message("makeTea");
                message.destinationName = "public/i339762_martijnbooij/";
                // Send the message
                client.send(message);

                document.getElementById('teaCount').innerHTML = parseInt(document.getElementById('teaCount').innerHTML) + 1;

                UpdateBarGraph();
            });

            $('#tbAddMessage').keypress(function(e) {
                var key = e.which;
                if (key == 13) // the enter key code
                {
                    $('#btnAddMessage').click();
                    return false;
                }
            }).focus();
        });

        window.onload = function () {

        CanvasJS.addColorSet("shades",
            [
            "#90EE90",
            "#008080",
            "#2E8B57",               
            ]);

        chart = new CanvasJS.Chart("chartContainer", {
        colorSet: "shades",
        animationEnabled: true,
        theme: "light2",
        title:{
            text: "Statistics"
        },
        axisY: {
            title: "Number",
            titleFontColor: "black"
        },
        data: [{        
            type: "column",  
            showInLegend: true, 
            legendMarkerColor: "black",
            legendText: "Drink",
            dataPoints: [      
                { y: coffee,  label: "Coffee" },
                { y: chocolateMilk,  label: "Chocolate Milk" },
                { y: tea,  label: "Tea" },
                { y: total, label: "Total"}
            ]
            }]
        });

        chart.render();
        }

        function UpdateBarGraph()
        {
            if (connection)
            {
                total = parseInt(document.getElementById('coffeeCount').innerHTML) + parseInt(document.getElementById('chocolateCount').innerHTML) + parseInt(document.getElementById('teaCount').innerHTML);
                //window.alert(tea);

                chart.options.data[0].dataPoints[0].y = parseInt(document.getElementById('coffeeCount').innerHTML);
                chart.options.data[0].dataPoints[1].y = parseInt(document.getElementById('chocolateCount').innerHTML);
                chart.options.data[0].dataPoints[2].y = parseInt(document.getElementById('teaCount').innerHTML);
                chart.options.data[0].dataPoints[3].y = total;

                //$sql = "INSERT INTO Drinks (Coffee, ChocolateMilk, Tea) VALUES ('$coffee', '$chocolateMilk', '$tea')";

                chart.render();
            }
        }

    </script>

    <?php
        $sql = "UPDATE Drinks SET Coffee = Coffee + " . "1";
        $result = $conn->query($sql);

        $sql = "UPDATE Drinks SET ChocolateMilk = ChocolateMilk + " . "1";
        $result = $conn->query($sql);

        $sql = "UPDATE Drinks SET Tea = Tea + " . "1";
        $result = $conn->query($sql);     
        $conn->close();   
        ?>

</body>
</html>