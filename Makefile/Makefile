TOPDIR:=$(CURDIR)
LC_ALL:=C
LANG:=C
export TOPDIR LC_ALL LANG

VAR_A:=A

world:

ifneq ($(READY_BUILD),1)
empty:=
space:=$(empty) $(empty)
_SINGLE=export MAKEFLAGS=$(space);

override READY_BUILD=1
export READY_BUILD
READY_BUILD=0

%::
	@echo $(VAR_A)
	@echo $(TOPDIR)
	@echo $(READY_BUILD)
	make -r $@
else
world:
	@echo "start to build"

.PHONY: world
endif

VAR_A:=B
$(warning $(VAR_A))

define debug
$(if $(1),$(warning "success"),$(warning "failed"))
$$(if $(1),$$(warning "success"),$$(warning "failed"))
endef

$(eval $(call debug,0))
