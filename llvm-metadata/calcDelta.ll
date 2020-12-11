; ModuleID = 'calcDelta.bc'
source_filename = "calcDelta.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@Delta = common dso_local global float 0.000000e+00, align 4, !dbg !0

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @calcDelta(i32 %a, i32 %b, i32 %c) #0 !dbg !11 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %c.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %a.addr, metadata !15, metadata !DIExpression()), !dbg !16
  store i32 %b, i32* %b.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %b.addr, metadata !17, metadata !DIExpression()), !dbg !18
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !19, metadata !DIExpression()), !dbg !20
  %0 = load i32, i32* %b.addr, align 4, !dbg !21
  %1 = load i32, i32* %b.addr, align 4, !dbg !22
  %mul = mul nsw i32 %0, %1, !dbg !23
  %conv = sitofp i32 %mul to float, !dbg !21
  store float %conv, float* @Delta, align 4, !dbg !24
  %2 = load i32, i32* %a.addr, align 4, !dbg !25
  %mul1 = mul nsw i32 4, %2, !dbg !26
  %3 = load i32, i32* %c.addr, align 4, !dbg !27
  %mul2 = mul nsw i32 %mul1, %3, !dbg !28
  %conv3 = sitofp i32 %mul2 to float, !dbg !29
  %4 = load float, float* @Delta, align 4, !dbg !30
  %sub = fsub float %4, %conv3, !dbg !30
  store float %sub, float* @Delta, align 4, !dbg !30
  %5 = load float, float* @Delta, align 4, !dbg !31
  ret float %5, !dbg !32
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!7, !8, !9}
!llvm.ident = !{!10}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "Delta", scope: !2, file: !3, line: 1, type: !6, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0 (https://github.com/llvm/llvm-project.git d32170dbd5b0d54436537b6b75beaf44324e0c28)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "calcDelta.c", directory: "/home/jw/Documents/MSc/LLVM_Short_Course/llvm-course/llvm-metadata/Class_1")
!4 = !{}
!5 = !{!0}
!6 = !DIBasicType(name: "float", size: 32, encoding: DW_ATE_float)
!7 = !{i32 7, !"Dwarf Version", i32 4}
!8 = !{i32 2, !"Debug Info Version", i32 3}
!9 = !{i32 1, !"wchar_size", i32 4}
!10 = !{!"clang version 10.0.0 (https://github.com/llvm/llvm-project.git d32170dbd5b0d54436537b6b75beaf44324e0c28)"}
!11 = distinct !DISubprogram(name: "calcDelta", scope: !3, file: !3, line: 3, type: !12, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!12 = !DISubroutineType(types: !13)
!13 = !{!6, !14, !14, !14}
!14 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!15 = !DILocalVariable(name: "a", arg: 1, scope: !11, file: !3, line: 3, type: !14)
!16 = !DILocation(line: 3, column: 21, scope: !11)
!17 = !DILocalVariable(name: "b", arg: 2, scope: !11, file: !3, line: 3, type: !14)
!18 = !DILocation(line: 3, column: 28, scope: !11)
!19 = !DILocalVariable(name: "c", arg: 3, scope: !11, file: !3, line: 3, type: !14)
!20 = !DILocation(line: 3, column: 35, scope: !11)
!21 = !DILocation(line: 4, column: 10, scope: !11)
!22 = !DILocation(line: 4, column: 14, scope: !11)
!23 = !DILocation(line: 4, column: 12, scope: !11)
!24 = !DILocation(line: 4, column: 8, scope: !11)
!25 = !DILocation(line: 5, column: 15, scope: !11)
!26 = !DILocation(line: 5, column: 13, scope: !11)
!27 = !DILocation(line: 5, column: 19, scope: !11)
!28 = !DILocation(line: 5, column: 17, scope: !11)
!29 = !DILocation(line: 5, column: 11, scope: !11)
!30 = !DILocation(line: 5, column: 8, scope: !11)
!31 = !DILocation(line: 6, column: 9, scope: !11)
!32 = !DILocation(line: 6, column: 2, scope: !11)
