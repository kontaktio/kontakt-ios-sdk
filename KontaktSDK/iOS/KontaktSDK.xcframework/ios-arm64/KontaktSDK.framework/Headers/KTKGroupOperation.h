//
//  KontaktSDK
//  Version: 6.1.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

#import "KTKOperation.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KTKGroupOperation (Interface)
@interface KTKGroupOperation : KTKOperation

#pragma mark - Operation Properties
///--------------------------------------------------------------------
/// @name Operation Properties
///--------------------------------------------------------------------

/**
 *  A Boolean indicating whether the internal operation queue is currently suspended.
 */
@property (nonatomic, assign, readonly, getter=isSuspended) BOOL suspended;

/**
 *  A Boolean indicating whether the operations should be called in serial or concurrent mode.
 */
@property (nonatomic, assign, readonly, getter=isSerial) BOOL serial;

/**
 *  A block object to be executed when the group operation finishes.
 */
@property (nonatomic, copy, readwrite) void (^groupCompletion)(NSArray<NSError*>* _Nullable);

#pragma mark - Initialization Methods
///--------------------------------------------------------------------
/// @name Initialization Methods
///--------------------------------------------------------------------

/**
 *  Initializes and returns an operation object with the specified opertations group.
 *
 *  @param operations The operations array to be added to the group operation.
 *
 *  @return An initialized operation object.
 */
- (instancetype)initWithOperations:(NSArray <__kindof NSOperation*>* _Nullable)operations;

/**
 *  Initializes and returns an operation object with the specified opertations group.
 *
 *  @param operations    The operations array to be added to the group operation.
 *  @param maxConcurrent The number of max concurrent operations.
 *
 *  @return An initialized operation object.
 */
- (instancetype)initWithOperations:(NSArray <__kindof NSOperation*>* _Nullable)operations maxConcurrent:(NSUInteger)maxConcurrent;

/**
 *  Initializes and returns an operation object with the specified opertations group.
 *
 *  @param operations    The operations array to be added to the group operation.
 *  @param maxConcurrent The number of max concurrent operations.
 *  @param serial        A Boolean indicating whether the operations should be called in serial or concurrent mode.
 *
 *  @return An initialized operation object.
 */
- (instancetype)initWithOperations:(NSArray <__kindof NSOperation*>* _Nullable)operations maxConcurrent:(NSUInteger)maxConcurrent serial:(BOOL)serial;

#pragma mark - Operation Methods
///--------------------------------------------------------------------
/// @name Operation Methods
///--------------------------------------------------------------------

/**
 *  Adds the specified operation object to the group operation.
 *
 *  @param operation The operation object to be added to the group operation.
 */
- (void)addOperation:(__kindof NSOperation*)operation;

/**
 *  Adds the specified operation object to the group operation.
 *
 *  @param operation  The operation object to be added to the group operation.
 *  @param updateLast A Boolean indicating whether the operation should become last operation.
 */
- (void)addOperation:(__kindof NSOperation*)operation
          updateLast:(BOOL)updateLast;

/**
 *  Gets a current progress of the finished operations.
 *
 *  @return A current progress of the finished operations.
 */
- (double)currentProgress;

@end

NS_ASSUME_NONNULL_END
