
<%@page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Warehouse Robots System</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="description" content="Carrot Search FoamTree is a JavaScript/HTML5 tree map with physics-inspired layouts and animations. Free demo." />
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />

    <!-- 
         The style sheets are optional. They define a layout in which the size of the
         visualization adapts to the current size of the browser window. 
      -->
    <link rel="stylesheet" href="js/carrot/assets/2.0.3/optional/css/common.css" />
    <script src="js/jquery-1.9.1.min.js"></script>
    <!--<link rel="stylesheet" href="js/carrot/assets/2.0.3/optional/css/layout.css" />-->
</head>

<body class="dark">
<!-- Some basic HTML scaffolding, optional. -->
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
    <div id="visualization" style="width:400px;height:400px;"></div>


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
                console.log("Group ",groupId.topmostClosedGroup.label);
                jQuery.ajax(
                        {
                            url:'MainController'

                        }
                );
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
</body>
</html>
