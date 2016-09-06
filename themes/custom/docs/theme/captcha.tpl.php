<?php

$captcha = theme_captcha($element);
if (strncmp($element["element"]["#captcha_type"], "hidden_captcha/", 15) == 0) {
  //generate a random class name
  $chars = "abcdfghjkmnpqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  $class = "";
  for ($i = 0; $i < 64; ++$i) $class .= substr($chars, rand(0, strlen($chars)-1), 1);
  //hide the random class via css
  drupal_add_css(".$class{width:0;height:0;overflow:hidden;}","inline"); // TODO: move the random class to an external file
  //html for the captcha
  $captcha = "<div class=\"$class uk-form-row\">" . $captcha . "</div>";
}
print $captcha;
