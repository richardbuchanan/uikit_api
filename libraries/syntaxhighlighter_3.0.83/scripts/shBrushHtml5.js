SyntaxHighlighter.brushes.Html5 = function()
{
  var tags = 'html body head title script link a p div span fieldset select input option button';

  this.regexList = [
    { regex: /(.+!DOCTYPE.+)/gm, css: 'doctype' },
    { regex: /(\w+=)/gm, css: 'attribute' },

    { regex: new RegExp(this.getKeywords(tags), 'gmi'), css: 'tag' },

    { regex: SyntaxHighlighter.regexLib.xmlComments, css: 'comment' },
    { regex: SyntaxHighlighter.regexLib.doubleQuotedString, css: 'value' }
  ];
};
SyntaxHighlighter.brushes.Html5.prototype = new SyntaxHighlighter.Highlighter();
SyntaxHighlighter.brushes.Html5.aliases   = ['html5'];