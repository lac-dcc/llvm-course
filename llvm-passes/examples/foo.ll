; ModuleID = 'llvm-ir/foo.ll'
source_filename = "llvm-ir/foo.ll"

define i32 @foo(i32 %a, i32 %b) {
  %c = add i32 1, 2
  %d = add i32 3, 4
  %e = add i32 %a, %b
  %f = add i32 %c, %d
  %g = add i32 %e, %f
  ret i32 %g
}
