jQuery.noConflict();
jQuery(function ($) {

    SearchAutocomplete = Backbone.View.extend({
        url: null,
        result: null,
        suggest: null,
        query: null,
        delay: 100,
        store: 1,
        queryMinChars: 3,
        shown: false,

        events: {
            'keydown .UI-SEARCH': 'onKeydown',
            'keyup .UI-SEARCH': 'onKeyup',
            'blur .UI-SEARCH': 'onBlur',
            'focus .UI-SEARCH': 'onFocus',
            'change .UI-CATEGORY': 'onChangeCategory'
        },

        initialize: function () {
            var self = this;
            _.bindAll(self);
        },

        init: function (el) {
            var self = this;

            self.setElement(el);

            self.url = self.$el.attr('data-url');
            self.delay = self.$el.attr('data-delay');
            self.queryMinChars = self.$el.attr('data-minchars');
            self.store = self.$el.attr('data-store');
            self.$listenField = $('.UI-SEARCH', self.$el);
            self.$suggestField = $('.UI-SEARCH-SUGGEST', self.$el);
            self.$placeholder = $('.UI-PLACEHOLDER', self.$el);
            self.$loader = $('.UI-LOADER', self.$el);
            self.$category = $('.UI-CATEGORY', self.$el);
            self.$categoryText = $('.UI-CATEGORY-TEXT', self.$el);
            self.result = '';
            self.query = self.$listenField.val();

            self.baseWidth = $('.UI-NAV-INPUT').width();

            self.onChangeCategory();
        },

        onChangeCategory: function () {
            var self = this;
            var text = $('option:selected', self.$category).text();

            if (self.$categoryText.length) {
                self.$categoryText.html(text);
                var width = self.$categoryText.width();

                if (width < 0) {
                    width = 20;
                }
                $('.UI-NAV-INPUT').css('padding-left', width + 35);
                $('.UI-CATEGORY').css('width', width + 35);
                // $('.UI-NAV-INPUT').css('width', self.baseWidth -(self.$categoryText.width() + 35));
            }

            self.result = '';
        },

        onKeydown: function (e) {
            var self = this;
            e.stopPropagation();

            if (!self.shown) {
                return;
            }

            switch (e.keyCode) {
                case 13: // enter
                    return;

                case 9: // tab
                case 27: // escape
                    e.preventDefault();
                    break;

                case 38: // up arrow
                    e.preventDefault();
                    self.prev();
                    break;

                case 40: // down arrow
                    e.preventDefault();
                    self.next();
                    break;
            }
        },

        onKeyup: function (e) {
            var self = this;
            e.stopPropagation();
            e.preventDefault();

            switch (e.keyCode) {
                case 40: // down arrow
                case 38: // up arrow
                    break;

                case 27: // escape
                    self.hide();
                    break;

                case 13:
                    if (!self.shown) {
                        return;
                    }

                    if ($('.active', self.$placeholder).length) {
                        self.select();
                    }
                    break;

                default:
                    var q = self.$listenField.val();
                    window.setTimeout(function () {
                        if (q == self.$listenField.val() && self.$listenField.val() != self.query) {
                            self.lookup();
                        }
                    }, self.delay);

                    self.$placeholder.html(self.result);
                    self.highlighter(self.$placeholder);
            }
        },

        onBlur: function (e) {
            var self = this;

            setTimeout(function () {
                self.select();
            }, 300);
        },

        onFocus: function (e) {
            var self = this;

            if (self.query.length >= self.queryMinChars) {
                if (self.result == '') {
                    self.lookup();
                } else {
                    self.show();
                }
            }
        },

        mouseover: function (e) {
            var self = this;

            $('.active', self.$placeholder).removeClass('active');

            $(e.currentTarget).addClass('active');
        },

        mouseout: function (e) {
            $(e.currentTarget).removeClass('active');
        },

        click: function (e) {
            var self = this;
            e.stopPropagation();
            e.preventDefault();

            self.select();
        },

        next: function (e) {
            var self = this;
            var next;

            var $active = $('.active', self.$placeholder);
            $active.removeClass('active');

            if ($active.length === 0) {
                next = $($('li', self.$placeholder).get(0));
            } else {
                next = $active.next();
            }

            if (next) {
                next.addClass('active');
            }
        },

        prev: function (e) {
            var self = this;
            var prev;

            var active = $('.active', self.$placeholder);
            active.removeClass('active');

            if (active.length === 0) {
                prev = $($('li', self.$placeholder).get($('li', self.$placeholder).length - 1));
            } else {
                prev = active.prev();
            }

            if (prev) {
                prev.addClass('active');
            }
        },

        select: function () {
            var self = this;

            if ($('.active', self.$placeholder).length) {
                var val = $('.active', self.$placeholder).attr('data-url');
                window.location.href = val;
            }

            return this.hide();
        },

        lookup: function () {
            var self = this;

            self.query = self.$listenField.val();
            if (self.query.length >= self.queryMinChars) {
                self.process(self.query);
            } else {
                self.hide(); jQuery('.UI-SEARCH').trigger('notEnoughCharacters');//JJJ
            }
        },

        process: function (query) {
            var ts = new Date().getTime();
            var self = this;

            query = query.replace(/<\/?[^>]+>/gi, '');

            var cat = '';

            if (self.$category.val() !== undefined) {
                cat = '&' + self.$category.attr('name') + '=' + self.$category.val();
            }

            $.ajax({
                url: self.url + '?q=' + encodeURIComponent(query) + cat + '&store=' + self.store,
                dataType: 'json',
                type: 'GET',
                beforeSend: function () {
                    clearTimeout(self.processTimer);
                    self.processTimer = setTimeout(function () {
                        self.$loader.show();
                    }, 250);
                },
                success: function (response) {
                    clearTimeout(self.processTimer);
                    console.log("d: " + (new Date().getTime() - ts));
                    self.$loader.hide();

                    if($.trim(self.$listenField.val()) != "")
                    {
                        if (response.query.toLowerCase().trim() === self.$listenField.val().toLowerCase().trim()) {
                            if (response.items.length) {
                                self.show(response.items);
                                $('.searchautocomplete-placeholder > ul li').each(function(){
                                    if($('.price-box .priceRange',$(this)).length > 0){
                                        $('.price-box .regular-price > .price',$(this)).css('display','none');
                                        $('.price-box .old-price',$(this)).css('display','none');
                                        $('.price-box .special-price',$(this)).css('display','none');
                                        $('.priceRange',$(this)).css('display','block');
                                    }
                                    console.log(2);
                                });
                                console.log(3);
                            } else {
                                self.hide(); jQuery('.UI-SEARCH').trigger('noResults');//JJJ
                            }
                        }
                    }

                    console.log(new Date().getTime() - ts);
                }
            });
        },

        show: function (html) {
            var self = this;

            if (html == -undefined) {
                if (self.result === '') {
                    return;
                }
            } else {
                self.result = html;
                self.$placeholder.html(html);
                self.highlighter(self.$placeholder);
            }

            self.$placeholder.show();
            self.$el.addClass('active');
            self.shown = true;

            $('li', self.$placeholder).each(function (key, el) {
                var $el = $(el);
                $el.on('mouseover', self.mouseover);
                $el.on('mouseout', self.mouseout);
                $el.on('click', self.click);
            });

            return this;
        },

        hide: function () {
            var self = this;

            self.$placeholder.hide();
            self.$el.removeClass('active');
            self.shown = false;

            return this;
        },

        highlighter: function (item) {
            var self = this;

            $('.highlight', item).each(function (key, el) {
                var $el = $(el);
                var arQuery = self.$listenField.val().split(' ');
                var html = $el.text();

                arQuery.each(function (word) {
                    if ($.trim(word)) {
                        word = word.replace(/[\-\[\]{}()*+?.,\\\^$|#\s]/g, '\\$&');
                        if ("strong".indexOf(word.toLowerCase()) == -1) {
                            html = html.replace(new RegExp('(' + word + '(?![^<>]*>))', 'ig'), function ($1, match) {
                                return '<strong>' + match + '</strong>';
                            });
                        }
                    }
                });

                $el.html(html);
            });
        }
    });

    $(function () {
        _.each($('.UI-SEARCHAUTOCOMPLETE'), function (el) {
            var autocomplete = new SearchAutocomplete();
            autocomplete.init(el);
        });
    });

});