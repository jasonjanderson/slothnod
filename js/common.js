var NUM_AVATAR = 15;

function expand_avatar(tweet_id, avatar) {
  var i = 0;
  $.each(avatar, function(k, v) {
    if (i < NUM_AVATAR) {
      i++;
      return;
    }
    format_avatar(k, v, true).prependTo($("div#avatar-container_"+tweet_id));
  });
  $("a#more_"+tweet_id).text("Less");
  return;
}

function toggle_avatar(tweet_id, avatar) {
  if ($('div#avatar-container_'+tweet_id+' a.expand-avatar').length == 0) {
    expand_avatar(tweet_id, avatar);
  } else {
    collapse_avatar(tweet_id);
  }
  return;
}

function format_avatar(username, url, expand_avatar) {
  var img = $("<img/>").attr("src", url).attr("title", username).attr("height", 45).attr("width", 45);
  var link = $("<a>").attr("href", "http://twitter.com/"+username);
  if (expand_avatar == true) {
    link.attr("class", "expand-avatar");
  }
  img.appendTo(link);
  return link;
}
 

function collapse_avatar(tweet_id) {
  $('div#avatar-container_'+tweet_id+' a.expand-avatar').remove();
  $("a#more_"+tweet_id).text("More");
  return;
}

function list_avatar(tweet_id, avatar, num) {
  var i = 0;
  $.each(avatar, function(k, v) {
    if (i == num) return;
    i++;
    format_avatar(k, v, false).prependTo($("div#avatar-container_"+tweet_id));
  });
}

function init_avatar(num) {
  $.each(tweets, function(k, v) {
      list_avatar(v, eval('avatar_'+v), num);
  });
}

function create_favorite(tweet_id) {
  $.ajax({
    type: "GET",
    url: "create_favorite",
    data: "id="+tweet_id,
    success: function(msg){
      swap_fav_image(tweet_id);
    }
  });
}

function swap_fav_image(tweet_id) {
  var img = $("<img/>").attr("src", "./images/star_yellow.png").attr("height", "16").attr("width", "16");
  $("a#fav_"+tweet_id).replaceWith(img);
}

