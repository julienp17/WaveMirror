jQuery.noConflict();
jQuery(function($) {

SearchAutocompleteForm = Backbone.View.extend({
    events : {
        'focus .UI-SEARCH' : 'focus',
        'blur .UI-SEARCH'  : 'blur',
        'submit'           : 'submit'
    },

    initialize: function() {
        var self = this;
        _.bindAll(self);
    },

    init: function(el) {
        var self = this;
        self.setElement(el);

        self.$field    = $('.UI-SEARCH', self.$el);
        self.emptyText = self.$el.attr('data-tip');

        self.blur();
    },

    submit: function(e) {
        var self = this;

        if (self.$field.val() == self.emptyText || self.$field.val() == '') {
            e.stopPropagation();
            return false;
        }
        var query = self.$field.val();
        query = query.replace(/<\/?[^>]+>/gi, '');
        self.$field.val(query);

        return true;
    },

    focus: function() {
        var self = this;

        if(self.$field.val() == self.emptyText){
            self.$field.val('');
        }
    },

    blur: function() {
        var self = this;

        if(self.$field.val() == ''){
            self.$field.val(self.emptyText);
        }
    }

});

$(function() {
    _.each($('.UI-SEARCHAUTOCOMPLETE'), function (el) {
        var form = new SearchAutocompleteForm();
        form.init(el);
    });
});

});