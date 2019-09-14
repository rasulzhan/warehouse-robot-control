(function($) {
  $.fn.aboutFoamTreeHtml5 = function(iframeMode) {
    var imgPathPrefix, dataPathPrefix;
    if (iframeMode) {
      imgPathPrefix = "..";
      dataPathPrefix = "../../../../data/";
    } else {
      imgPathPrefix = "assets/2.0.3/optional";
      dataPathPrefix = "data/";
    }

    var $this = this;
    var optionTransitionFrame;
    var colorModelFrame = 0;

    var requestAnimFrame = function () {
      return (
        window["requestAnimationFrame"] ||
        window["webkitRequestAnimationFrame"] ||
        window["mozRequestAnimationFrame"] ||
        window["oRequestAnimationFrame"] ||
        window["msRequestAnimationFrame"] ||
        function (callback) {
          var lastDuration = 0;
          window.setTimeout(function() {
            var start = Date.now();
            callback();
            lastDuration = Date.now() - start;
          }, lastDuration < 16 ? 16 - lastDuration : 0);
        }
      );
    }();

    $(window).unload(function() {
      foamtree.set("onModelChanged", null);
    });

    var features = [
      {
        id: "datasets",
        title: "Data sets",
        image: "tile-datasets.png",
        description: "<em class='brand'>Carrot Search FoamTree</em> visualizes hierarchical data sets:",
        type: "stateful",
        presets: 5,
        links: [
          {
            title: "Search",
            links: [
              {
                id: "topics",
                group: "datasets",
                text: "by topic",
                presets: {4: true},
                active: true,
                action: function() {
                  loadJson("data-mining-100-topic-hierarchical.jsonp");
                }
              },
              {
                id: "domains",
                group: "datasets",
                text: "by domain",
                presets: {0: true},
                action: function() {
                  loadJson("data-mining-100-url-hierarchical.jsonp");
                }
              }
            ]
          },
          {
            title: "Data",
            links: [
              {
                id: "coffee",
                group: "datasets",
                text: "Coffee",
                presets: {1: true},
                action: function() {
                  foamtree.set({
                    groupColorDecorator: function(opts, params, vars) {
                      vars.labelColor = "auto";
                      switch (params.group.label) {
                        case "Aromas":
                          vars.groupColor = "rgba(200,200,200,.5)";
                          vars.labelColor = "rgb(240,240,240)";
                          break;
                        case "Sugar Browning":   vars.groupColor = "rgb(251, 180, 174)"; break;
                        case "Enzymatic":        vars.groupColor = "rgb(179, 205, 227)"; break;
                        case "Dry Distillation": vars.groupColor = "rgb(204, 235, 197)"; break;

                        case "Tastes":
                          vars.groupColor = "rgba(200,200,200,.5)";
                          vars.labelColor = "rgb(240,240,240)";
                          break;
                        case "Bitter": vars.groupColor = "rgb(222, 203, 228)"; break;
                        case "Salt":   vars.groupColor = "rgb(254, 217, 166)"; break;
                        case "Sweet":  vars.groupColor = "rgb(255, 255, 204)"; break;
                        case "Sour":   vars.groupColor = "rgb(229, 216, 189)"; break;
                      }
                    },
                    groupGradientType: "darkening"
                  });
                  loadJson("coffee.jsonp");
                }
              },
              {
                id: "nba",
                group: "datasets",
                text: "NBA salaries",
                presets: {2: true},
                action: function() {
                  loadJson("nba-salaries.jsonp");
                }
              }
            ]
          },
          {
            title: "Other",
            links: [
              {
                id: "multilingual",
                group: "datasets",
                text: "Multilingual",
                presets: {3: true},
                action: function() {
                  loadJson("multilingual.jsonp");
                }
              }
            ]
          }
        ],
        after: function() {
        }
      },

      {
        title: "Animations",
        image: "tile-animations.png",
        description: "<strong>Animation</strong> styles and speeds:",
        type: "stateful",
        presets: 3,
        links: [
          {
            links: [
              {
                group: "animation",
                active: true,
                text: "Auto",
                presets: { 2: true },
                action: function() {
                  foamtree.set("rolloutType", "auto");
                }
              },
              {
                group: "animation",
                text: "Explode",
                presets: { 0: true },
                action: function() {
                  foamtree.set("rolloutType", "explode");
                }
              },
              {
                group: "animation",
                text: "Fade",
                presets: { 1: true },
                action: function() {
                  foamtree.set("rolloutType", "fadein");
                }
              },
              {
                group: "animation",
                text: "None",
                presets: { },
                action: function() {
                  foamtree.set("rolloutType", "none");
                }
              }
            ]
          },
          {
            links: [
              {
                group: "animation-speed",
                text: "Fast",
                presets: { 1: true },
                action: function() {
                  foamtree.set({
                    "rolloutSpeed": 10,
                    "rolloutRate": 5
                  });
                }
              },
              {
                group: "animation-speed",
                text: "Medium",
                active: true,
                presets: { 2: true },
                action: function() {
                  foamtree.set({
                    "rolloutSpeed": 5,
                    "rolloutRate": 5
                  });
                }
              },
              {
                group: "animation-speed",
                text: "Slow",
                presets: { 0: true },
                action: function() {
                  foamtree.set({
                    "rolloutSpeed": 1,
                    "rolloutRate": 1
                  });
                }
              }
            ]
          }
        ],
        after: function() {
          foamtree.rollout();
        }
      },

      {
        title: "Color models",
        image: "tile-color-models.png",
        description: "<strong>Color models:</strong>",
        type: "stateful",
        presets: 4,
        links: [
          {
            title: "Rainbow",
            links: [
              {
                group: "color-model",
                text: "Full",
                active: true,
                presets: {3: true},
                action: function() {
                  colorModelFrame = -1;
                  foamtree.set({
                    "rainbowStartColor": "hsla(0, 100%, 50%, 0.9)",
                    "rainbowEndColor": "hsla(300, 100%, 50%, 0.9)",
                    "groupColorDecorator": null
                  });
                  foamtree.redraw();
                }
              },
              {
                group: "color-model",
                text: "Blue-orange",
                presets: {0: true},
                action: function() {
                  colorModelFrame = -1;
                  foamtree.set({
                    "rainbowStartColor": "hsla(240, 100%, 50%, 0.9)",
                    "rainbowEndColor": "hsla(45, 100%, 50%, 0.9)",
                    "groupColorDecorator": null
                  });
                  foamtree.redraw();
                }
              }
            ]
          },
          {
            title: "Custom",
            links: [
              {
                group: "color-model",
                text: "Sentiment",
                presets: {1: true},
                action: function() {
                  // Generate some sentiment
                  colorModelFrame = -1;
                  generate();
                  foamtree.set("groupColorDecorator", function(opts, params, vars) {
                    var sentiment = params.group.sentiment;
                    if (sentiment == 0) {
                      vars.groupColor.s = 0;
                      vars.groupColor.l = 0;
                    } else {
                      if (sentiment > 0) {
                        vars.groupColor.h = 120;
                      } else {
                        vars.groupColor.h = 0;
                      }
                      vars.groupColor.s = 50 * (1 + Math.abs(sentiment));
                      vars.groupColor.l = Math.abs(60 * sentiment);
                      vars.groupColor.model = "hsl";
                      vars.labelColor = "auto";
                    }
                  });
                  foamtree.set("onModelChanged", generate);
                  foamtree.redraw();
                  return;

                  function generate() {
                    generateSentiment(foamtree.get("dataObject").groups, 0, 0);
                  }

                  function generateSentiment(groups, base, level) {
                    for (var i = 0; i < groups.length; i++) {
                      var group = groups[i];
                      var s = Math.max(-1, Math.min(1, base + Math.pow(2, 1 - level) * Math.random() - 1));
                      s = s * s * s * s * s;
                      group.sentiment = s;
                      if (group.groups) {
                        generateSentiment(group.groups, s, level + 1);
                      }
                    }
                  }
                }
              },
              {
                group: "color-model",
                text: "Radar",
                presets: {2: true},
                action: function() {
                  if (colorModelFrame > 0) {
                    return;
                  }
                  foamtree.set("groupColorDecorator", function(opts, params, vars) {
                    if (params.level == 0) {
                      var delay = 5;
                      var count = 3;
                      var frameDiv = Math.floor(colorModelFrame / delay);
                      var mod = frameDiv % params.siblingCount;
                      var diff = (mod - params.index + params.siblingCount) % params.siblingCount;
                      if (diff < count) {
                        vars.groupColor.g = 255 * (1 - ((diff * delay + colorModelFrame % delay) / (delay * count)));
                      } else {
                        vars.groupColor.g = 0;
                      }
                      vars.groupColor.r = 0;
                      vars.groupColor.b = 0;
                      vars.groupColor.model = "rgb";
                      vars.labelColor = "auto";
                    }
                  });
                  colorModelFrame = 0;

                  requestAnimFrame(function redraw() {
                    if (colorModelFrame < 0) {
                      return;
                    }
                    foamtree.redraw();
                    colorModelFrame++;
                    requestAnimFrame(redraw);
                  });
                }
              }
            ]
          }
        ],
        after: function() {
        }
      },

      {
        title: "Borders",
        image: "tile-borders.png",
        description: "Width and radius of <strong>borders</strong>:",
        type: "stateful",
        presets: 4,
        links: [
          {
            links: [
              {
                group: "border",
                text: "Thick",
                presets: { 0: true },
                options: {
                  "groupBorderWidth": 12,
                  "groupInsetWidth": 12
                }
              },
              {
                group: "border",
                text: "Med",
                active: Math.min(screen.width, screen.height) >= 600,
                presets: { 3: true },
                options: {
                  "groupBorderWidth": 6,
                  "groupInsetWidth": 6
                }
              },
              {
                group: "border",
                text: "Thin",
                active: Math.min(screen.width, screen.height) < 600,
                presets: { 1: true },
                options: {
                  "groupBorderWidth": 2,
                  "groupInsetWidth": 2
                }
              },
              {
                group: "border",
                text: "None",
                presets: { 2: true },
                options: {
                  "groupBorderWidth": 0,
                  "groupInsetWidth": 0
                }
              }
            ]
          },
          {
            links: [
              {
                group: "radius",
                text: "Rounded",
                active: true,
                presets: { 3: true },
                options: {
                  "groupBorderRadius": 0.35
                }
              },
              {
                group: "radius",
                text: "Straight",
                presets: { 0: true, 2: true },
                options: {
                  "groupBorderRadius": 0
                }
              },
              {
                group: "radius",
                text: "Oval",
                presets: { 1: true },
                options: {
                  "groupBorderRadius": 1
                }
              }
            ]
          }
        ],
        after: function() {
          foamtree.redraw();
        }
      },

      {
        title: "Labels",
        image: "tile-labels.png",
        description: "Size, font and color of <strong>labels</strong>:",
        type: "stateful",
        presets: 3,
        links: [
          {
            links: [
              {
                group: "label-size",
                text: "Large",
                active: true,
                presets: { 2: true },
                action: function() {
                  foamtree.set("groupMaxFontSize", "22%");
                }
              },
              {
                group: "label-size",
                text: "Medium",
                presets: { 0: true },
                action: function() {
                  foamtree.set("groupMaxFontSize", "15%");
                }
              },
              {
                group: "label-size",
                text: "Small",
                presets: { 1: true },
                action: function() {
                  foamtree.set("groupMaxFontSize", "10%");
                }
              }
            ]
          },
          {
            links: [
              {
                group: "label-font",
                text: "Impact",
                active: true,
                presets: { 2: true },
                action: function() {
                  foamtree.set("groupFontFamily", "Impact, Charcoal, sans-serif");
                }
              },
              {
                group: "label-font",
                text: "Serif",
                presets: { 0: true },
                action: function() {
                  foamtree.set("groupFontFamily", "Georgia, Georgia, serif");
                }
              },
              {
                group: "label-font",
                text: "Sans-serif",
                presets: { 1: true },
                action: function() {
                  foamtree.set("groupFontFamily", "Arial, Helvetica, sans-serif");
                }
              }
            ]
          },
          {
            links: [
              {
                group: "label-color",
                text: "Black",
                active: true,
                presets: { 2: true },
                action: function() {
                  foamtree.set("labelColorThreshold", 0.35);
                }
              },
              {
                group: "label-color",
                text: "White",
                presets: { 1: true },
                action: function() {
                  foamtree.set("labelColorThreshold", 0.95);
                }
              }
            ]
          }
        ],
        after: function() {
          foamtree.redraw();
        }
      },

      {
        title: "Selection",
        image: "tile-selection.png",
        description: "Programmatic control of selection and drill-down:",
        type: "stateless",
        presets: 4,
        links: [
          {
            links: [
              {
                group: "selection",
                text: "Select random",
                presets: { 0: true },
                action: function() {
                  var data = foamtree.get("dataObject");
                  var groupIds = addIds(data.groups, []);
                  var count = Math.max(1, Math.floor(0.4 * Math.random() * groupIds.length));
                  var toSelect = [];
                  for (var i = 0; i < count; i++) {
                    toSelect.push(groupIds[Math.floor(Math.random() * groupIds.length)]);
                  }
                  foamtree.set("selection", toSelect);
                  return;

                  function addIds(groups, ids) {
                    for (var i = 0; i < groups.length; i++) {
                      ids.push(groups[i].id);
                      if (groups[i].groups) {
                        addIds(groups[i].groups, ids);
                      }
                    }
                    return ids;
                  }
                }
              },
              {
                group: "selection",
                text: "Deselect all",
                presets: { 1: true },
                action: function() {
                  foamtree.set("selection", { all: true, selected: false });
                }
              }
            ]
          },
          {
            links: [
              {
                group: "expansion",
                text: "Open all",
                presets: { 2: true },
                action: function() {
                  foamtree.set("open", { all: true, open: true });
                }
              },
              {
                group: "expansion",
                text: "Close all",
                presets: { 3: true },
                action: function() {
                  foamtree.set("open", { all: true, open: false });
                }
              }
            ]
          }
        ],
        after: function() { }
      },
      {
        title: "Mobile",
        type: "stateless",
        image: "tile-mobile.png",
        description: "Mobile support",
        presets: 1,
        links: [
          {
            group: "selection",
            text: "See the mobile demo",
            action: function() {
              window.parent.document.location.href = "../../../../mobile.html";
            },
            presets: {0: true}
          }
        ],
        after: function() { }
      }
    ];
    
    var $tiles = $("<ul class='tiles'></ul>");
    for (var i = 0; i < features.length; i++) {
      var feature = features[i];
      var $featureLi = $("<li />").appendTo($tiles);
      
      var $a = $("<a href='#'><img width='122' height='100' src='" + imgPathPrefix + "/img/" +
        feature.image + "' alt='" + feature.title + "' /></a>")
          .appendTo($featureLi).data("feature", feature).click(function() {
          var feature = $(this).data("feature");
          if (feature.presets) {
            var preset = $(this).data("preset") || 0;

            $(this).parent().find("a").removeClass("active");

            var hasOptions = false;
            var allOptions = { };
            for (var j = 0; j < feature.links.length; j++) {
              var link = feature.links[j];
              if (link.links) {
                for (var k = 0; k < link.links.length; k++) {
                  var ll = link.links[k];
                  if (ll.presets[preset]) {
                    if (ll.action) {
                      ll.action();
                    }
                    if (ll.options) {
                      $.extend(allOptions, ll.options);
                      hasOptions = true;
                    }
                    ll.$link.addClass("active");
                  }
                }
              } else {
                if (link.presets[preset]) {
                  if (link.action) {
                    link.action();
                  }
                  if (link.options) {
                    $.extend(allOptions, link.options);
                    hasOptions = true;
                  }
                  link.$link.addClass("active");
                }
              }
            }
            if (hasOptions) {
              foamtree.set(allOptions);
            }
            feature.after();
            $(this).data("preset", (preset + 1) % feature.presets);
          }
          return false;
      });

      $featureLi.append("<p>" + feature.description + "</p>");

      var $linksUl = $("<ul class='" + feature.type + "' />").appendTo($featureLi);
      for (var j = 0; j < feature.links.length; j++) {
        var $linkLi = $("<li />").appendTo($linksUl);
        var link = feature.links[j];
        if (link.links) {
          if (link.title) {
            $linkLi.append("<span>" + link.title + ": </span>");
          }
          for (var k = 0; k < link.links.length; k++) {
            var linklink = link.links[k];
            addLinkTo($linkLi, linklink, feature.after);
          }
        } else {
          addLinkTo($linkLi, link, feature.after);
        }
      }
    }

    $this.html($tiles);

    $tiles.append('<li class="extras"><p>Next steps: ' +
      (iframeMode ? '<a href="settings.html">Experiment more</a> | ' : "") +
      (iframeMode ? '<a href="api.html">Read API docs</a> | ' : '<a target="_blank" href="' + imgPathPrefix + '/html/api.html">Read API docs</a> | ') +
      (iframeMode ? '<a class="download" href="download.html">Download this demo</a> | ' : "") +
      '<a href="http://carrotsearch.com/contact" target="_blank">Contact us for licensing</a>\
      </p><p>See also: <a href="http://download.carrotsearch.com/circles/demo" target="_blank">Circles visualization</a> | \
      <a href="http://carrotsearch.com/lingo3g" target="_blank">Lingo3G document clustering engine</a></p>\
    </li>');
    return $this;

    function addLinkTo($target, link, after) {
      var $linkA = $("<a></a>").text(link.text).attr("href", "#").addClass(link.group).appendTo($target);
      if (link.active) {
        $linkA.addClass("active");
        if (link.options && link.active) {
          foamtree.set(link.options);
        }
      }
      $linkA.click(function() {
        $("a." + link.group).removeClass("active");
        $(this).addClass("active");
        if (link.action) {
          link.action();
        }
        after();
        if (link.options) {
          foamtree.set(link.options);
          foamtree.redraw();
        }
        return false;
      });
      link.$link = $linkA;
    }

    function loadJson(path) {
      (iframeMode ? window.parent.CarrotSearchDemoHelper : CarrotSearchDemoHelper).loading(true);
      $.ajax({
        url: dataPathPrefix + path,
        dataType: "jsonp",
        jsonpCallback: "modelDataAvailable",
        success: function(data) {
          // Nothing to do in non-iframe mode -- the callback function
          // is already defined in index.html and sets the new dataObject option.
          if (iframeMode) {
            foamtree.set("dataObject", data);
          }
        }
      });
    }
  };
})(jQuery);
