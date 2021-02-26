; ModuleID = 'simple-integer.bc'
source_filename = "simple-integer.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@c1 = dso_local global i32 17, align 4, !dbg !0
@.str = private unnamed_addr constant [8 x i8] c"C3= %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"Pointer= %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [12 x i8] c"Output= %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !11 {
entry:
  %c2 = alloca i32, align 4
  %c3 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %c2, metadata !14, metadata !DIExpression()), !dbg !15
  store i32 25, i32* %c2, align 4, !dbg !15
  call void @llvm.dbg.declare(metadata i32* %c3, metadata !16, metadata !DIExpression()), !dbg !17
  %0 = load i32, i32* @c1, align 4, !dbg !18
  %1 = load i32, i32* %c2, align 4, !dbg !19
  %add = add nsw i32 %0, %1, !dbg !20
  store i32 %add, i32* %c3, align 4, !dbg !17
  call void @llvm.dbg.value(metadata i32* %c2, metadata !21, metadata !DIExpression()), !dbg !23
  store i32 3, i32* %c2, align 4, !dbg !24
  %2 = load i32, i32* %c3, align 4, !dbg !25
  %cmp = icmp sgt i32 %2, 41, !dbg !27
  br i1 %cmp, label %if.then, label %if.else, !dbg !28

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %c2, align 4, !dbg !29
  call void @llvm.dbg.value(metadata i32 %3, metadata !31, metadata !DIExpression()), !dbg !23
  %4 = load i32, i32* %c2, align 4, !dbg !32
  call void @llvm.dbg.value(metadata i32 %4, metadata !33, metadata !DIExpression()), !dbg !23
  br label %if.end, !dbg !34

if.else:                                          ; preds = %entry
  %5 = load i32, i32* @c1, align 4, !dbg !35
  call void @llvm.dbg.value(metadata i32 %5, metadata !31, metadata !DIExpression()), !dbg !23
  call void @llvm.dbg.value(metadata i32* %c3, metadata !21, metadata !DIExpression()), !dbg !23
  call void @llvm.dbg.value(metadata i32 %5, metadata !33, metadata !DIExpression()), !dbg !23
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %p1.0 = phi i32* [ %c2, %if.then ], [ %c3, %if.else ], !dbg !23
  %out.0 = phi i32 [ %3, %if.then ], [ %5, %if.else ], !dbg !37
  call void @llvm.dbg.value(metadata i32 %out.0, metadata !31, metadata !DIExpression()), !dbg !23
  call void @llvm.dbg.value(metadata i32* %p1.0, metadata !21, metadata !DIExpression()), !dbg !23
  %6 = load i32, i32* %c3, align 4, !dbg !38
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i64 0, i64 0), i32 %6), !dbg !39
  %7 = load i32, i32* %p1.0, align 4, !dbg !40
  %call1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i64 0, i64 0), i32 %7), !dbg !41
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.2, i64 0, i64 0), i32 %out.0), !dbg !42
  ret i32 0, !dbg !43
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!7, !8, !9}
!llvm.ident = !{!10}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "c1", scope: !2, file: !3, line: 3, type: !6, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0 (https://github.com/llvm/llvm-project.git d32170dbd5b0d54436537b6b75beaf44324e0c28)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "simple-integer.c", directory: "/home/jw/Documents/MSc/LLVM_Short_Course/LLVM_Metadata/Class_03/TrackingPass/example")
!4 = !{}
!5 = !{!0}
!6 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!7 = !{i32 7, !"Dwarf Version", i32 4}
!8 = !{i32 2, !"Debug Info Version", i32 3}
!9 = !{i32 1, !"wchar_size", i32 4}
!10 = !{!"clang version 10.0.0 (https://github.com/llvm/llvm-project.git d32170dbd5b0d54436537b6b75beaf44324e0c28)"}
!11 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 5, type: !12, scopeLine: 5, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!12 = !DISubroutineType(types: !13)
!13 = !{!6}
!14 = !DILocalVariable(name: "c2", scope: !11, file: !3, line: 6, type: !6)
!15 = !DILocation(line: 6, column: 6, scope: !11)
!16 = !DILocalVariable(name: "c3", scope: !11, file: !3, line: 7, type: !6)
!17 = !DILocation(line: 7, column: 6, scope: !11)
!18 = !DILocation(line: 7, column: 11, scope: !11)
!19 = !DILocation(line: 7, column: 16, scope: !11)
!20 = !DILocation(line: 7, column: 14, scope: !11)
!21 = !DILocalVariable(name: "p1", scope: !11, file: !3, line: 8, type: !22)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!23 = !DILocation(line: 0, scope: !11)
!24 = !DILocation(line: 10, column: 4, scope: !11)
!25 = !DILocation(line: 11, column: 5, scope: !26)
!26 = distinct !DILexicalBlock(scope: !11, file: !3, line: 11, column: 5)
!27 = !DILocation(line: 11, column: 7, scope: !26)
!28 = !DILocation(line: 11, column: 5, scope: !11)
!29 = !DILocation(line: 12, column: 9, scope: !30)
!30 = distinct !DILexicalBlock(scope: !26, file: !3, line: 11, column: 11)
!31 = !DILocalVariable(name: "out", scope: !11, file: !3, line: 9, type: !6)
!32 = !DILocation(line: 13, column: 8, scope: !30)
!33 = !DILocalVariable(name: "p2", scope: !11, file: !3, line: 8, type: !6)
!34 = !DILocation(line: 14, column: 2, scope: !30)
!35 = !DILocation(line: 16, column: 9, scope: !36)
!36 = distinct !DILexicalBlock(scope: !26, file: !3, line: 15, column: 6)
!37 = !DILocation(line: 0, scope: !26)
!38 = !DILocation(line: 20, column: 21, scope: !11)
!39 = !DILocation(line: 20, column: 2, scope: !11)
!40 = !DILocation(line: 21, column: 26, scope: !11)
!41 = !DILocation(line: 21, column: 2, scope: !11)
!42 = !DILocation(line: 22, column: 2, scope: !11)
!43 = !DILocation(line: 23, column: 2, scope: !11)
