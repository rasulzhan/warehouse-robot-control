<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <!--<meta http-equiv="refresh" content="1">-->
    <style>
        body{margin:0;
            background:url('images/d.png')  ;
            height:600px;
        }
        #back{

            padding-top:1%;
            background:rgba(204,204,204,0.8);
            margin-left:10%;
            margin-top:2.5%;
            height:100%;
            width:80%;
            border-radius: 10px;
            box-shadow:0 0 10px #000000;}
        #head{

            border-radius: 10px;
            height:20%;
            width:98%;
            margin-left:1%;
            background:#fff ;
            background-size:100%;
            font-family: 'robot';
            font-size: 400%;
            float: left;
            box-shadow:0 0 10px inset #000000;
        }
        @font-face{
            font-family: 'robot';
            src: url('images/Vdj.ttf');
        }

        #ras{

            float:left;
            margin-top:1%;
            height:70%;
            margin-left:1%;
            width:48.5%;
            background:rgba(255,255,255,1);
            border-radius: 10px;

        }
        #men{
            border-radius: 10px;

            float:right;
            display:inline-block;
            margin-top:1%;
            height:70%;
            margin-right:1%;
            width:48.5%;
            background:rgba(255,255,255,1);

        }
    </style>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>Склад</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />

    <!--
         The style sheets are optional. They define a layout in which the size of the
         visualization adapts to the current size of the browser window.
      -->
    <link rel="stylesheet" href="js/carrot/assets/2.0.3/optional/css/common.css" />
    <%--<script src="js/ember-latest.min.js"></script>--%>
    <script src="js/jquery-1.9.1.min.js"></script>
</head>

<body>
<div id='back'>
    <div id='head'>
        <img src='images/logo.png' style='margin-top:0.6%;margin-left:1%;width:13%;box-shadow:2px 2px 5px rgba(0,0,0,0.4);'>
        <span style='text-shadow:0px 0px 4px rgba(0,0,0,0.8),0 0 2px black ;color:white;'>IITU RoboLAB </span>

        <img src='images/it.png' style='margin-top:0.6%;margin-left:4%;width:13%;'>


    </div>
    <div id='ras'>
        <div id="main">
            <div id="gradient"></div>
            <!-- Crop marks -->
            <span class="cropmark horizontal topleft"></span>
            <span class="cropmark vertical topleft"></span>
            <span class="cropmark horizontal bottomright"></span>
            <span class="cropmark vertical bottomright"></span>


            <!--
               The element into which FoamTree is to be embedded (required). Make sure the
               element has an id (referenced in the script below) and non-zero width and height.
            -->
            <div id="visualization" style="width:523px;height:430px;"></div>


            <!-- Alternative content if JavaScript is disabled, optional -->
            <noscript>
                To use Carrot Search HTML5 FoamTree, enable JavaScript.
            </noscript>
        </div>

        <!-- Required JavaScripts -->
        <script src="js/carrot/assets/2.0.3/required/js/carrotsearch.foamtree.html5.min.js"></script>

        <!-- Embed visualization -->
        <script>
            var foamtree, supported;

            // Check if the browser supports FoamTree
            supported = CarrotSearchFoamTree.supported;

            // If supported, embed
            if (supported) {
                foamtree = new CarrotSearchFoamTree({
                    // Identifier of the DOM element into which to embed FoamTree
                    id: "visualization",
                    backgroundColor: "rgba(0, 0, 0, 0.3)",
                    onGroupDoubleClick:function(groupId) {
                        console.log("Group: ",groupId.topmostClosedGroup.label);

                        $.ajax({
                            url: "MainController?name="+encodeURIComponent(groupId.topmostClosedGroup.id),
                            cache: false,
                            contentType: "text/html;charset=UTF-8",
                            dataType: 'html',
                            success: function(html){
                                console.log("Html: ");
                                if(!$('#men').empty())
                                $("#men").remove();
                                console.log(html);
                                $("#men").append(html);
                            }
                        });
                    }
                });
            }

            // When JSON-P data is available, visualize it
            function modelDataAvailable(data) {
                if (foamtree) {
                    foamtree.set("dataObject", data);
                }
            }
        </script>

        <!-- Example data, wrapped in the modelDataAvailable() function call -->
        <script src="data-mining-100-topic-hierarchical.jsonp"></script>

    </div>
    <div id='men'>

    </div>
</div>
</body>
</html>
