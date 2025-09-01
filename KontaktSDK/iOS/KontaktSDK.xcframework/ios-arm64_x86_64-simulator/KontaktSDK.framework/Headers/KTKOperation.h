//
//  KontaktSDK
//  Version: 6.2.0
//
//  Copyright (c) 2015 Kontakt.io. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 *  KTKOperationState
 * 
 *  Operation state.
 */
typedef NS_ENUM(NSUInteger, KTKOperationState) {
    /**
     *  The operation is in unknown state.
     */
    KTKOperationStateUnknown      = -1,
    /**
     *  The initial state of an operation.
     */
    KTKOperationStateInitialized  = 0,
    /**
     *  The operation is pending for the ready state.
     */
    KTKOperationStatePending      = 1,
    /**
     *  The operation is ready to execute.
     */
    KTKOperationStateReady        = 2,
    /**
     *  The operation is executing.
     */
    KTKOperationStateExecuting    = 3,
    /**
     *  Execution of the operation has finished, but it has not yet notified the queue of this.
     */
    KTKOperationStateFinishing    = 4,
    /**
     *  The operation has finished executing.
     */
    KTKOperationStateFinished     = 5
};

#pragma mark - KTKOperation (Interface)
@interface KTKOperation : NSOperation

#pragma mark - Operation Properties
///--------------------------------------------------------------------
/// @name Operation Properties
///--------------------------------------------------------------------

/**
 *  The operation state.
 */
@property (nonatomic, assign, readwrite) KTKOperationState state;

/**
 *  A flag that tells if the operation entered `KTKOperationStateExecuting` state during its lifetime.
 */
@property (nonatomic, assign, readonly) BOOL didExecute;

#pragma mark - Operation Methods
///--------------------------------------------------------------------
/// @name Operation Methods
///--------------------------------------------------------------------

/**
 *  <code>execute</code> is the entry point of execution for all <code>KTKOperation</code> subclasses.
 *  If you subclass <code>KTKOperation</code> and wish to customize its execution, you would
 *  do so by overriding the <code>execute</code> method.
 *
 *  At some point, your <code>KTKOperation</code> subclass must call one of the <code>finish</code>
 *  methods defined below; this is how you indicate that your operation has
 *  finished its execution, and that operations dependent on yours can re-evaluate
 *  their readiness state.
 */
- (void)execute;

/**
 *  Cancels execution of the operation with specified errors.
 *
 *  @param errors An array of error objects.
 */
- (void)cancelWithErrors:(NSArray <NSError *>* _Nullable)errors;

/**
 *  Finishes execution of the operation.
 */
- (void)finish;

/**
 *  Finishes execution of the operation with the specified error.
 *
 *  @param error An error object.
 */
- (void)finishWithError:(NSError * _Nullable)error;

/**
 *  Subclasses may override <code>finished<code> if they wish to react to the operation finishing.
 *
 *  @param errors An array of error objects.
 */
- (void)finished:(NSArray <NSError *>* _Nullable)errors;

/**
 *  Indicates that the operation queue will begin enqueuing the operation.
 */
- (void)willEnqueue;

@end

NS_ASSUME_NONNULL_END
